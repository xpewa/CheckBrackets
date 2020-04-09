#include <stdio.h>
#include <stdlib.h>

char stek[100];

int k_quotes = 0;
int k_enter = 1;

int main(int argc, char *argv[])
{
    if (argc < 2){
        printf("Need file name.");
        return 1;
    }
    FILE *fp;
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error open of input file");
        return 1;
    }

    char open_need_find[3];
    for (int i = 0; i<3; i++) {open_need_find[i] = "";}
    if (strchr(argv[2], '(') != NULL) {open_need_find[0] = '(';}
    if (strchr(argv[2], '[') != NULL) {open_need_find[1] = '[';}
    if (strchr(argv[2], '{') != NULL) {open_need_find[2] = '{';}

    char close_need_find[3];
    for (int i = 0; i<3; i++) {close_need_find[i] = "";}
    if (strchr(argv[2], ')') != NULL) {close_need_find[0] = ')';}
    if (strchr(argv[2], ']') != NULL) {close_need_find[1] = ']';}
    if (strchr(argv[2], '}') != NULL) {close_need_find[2] = '}';}

    char ch = getc(fp);
    while (ch!=EOF) {
        int len = strlen(stek);
        if (ch == '\"') {k_quotes++;}
        if (ch == '\n') {k_enter++;}
        if ( ((k_quotes % 2 == 0) && (!strcmp("quotes", argv[3]))) || (strcmp("quotes", argv[3])) ) {
            if (strchr(open_need_find, ch) != NULL) {stek[len] = ch; goto loop;}
            if (strchr(close_need_find, ch) != NULL) {
                if (len <= 0) {printf("Not enough opening brakets. Error on line: %d", k_enter); return 1;}
                if (((ch == ')') && (stek[len-1] == '('))
                    || ((ch == ']') && (stek[len-1] == '['))
                    || ((ch == '}') && (stek[len-1] == '{')))
                    {stek[len-1] = '\0';}
                else {printf("Error on line: %d", k_enter); return 1;}
            }
        }
        loop:
        ch = getc(fp);
    }

        if (strlen(stek) == 0) {printf("All is OK.");}
        if (strlen(stek) != 0) {printf("Not enough closing brakets. Error on line: %d", k_enter);}

    fclose(fp);
    return 0;
}
