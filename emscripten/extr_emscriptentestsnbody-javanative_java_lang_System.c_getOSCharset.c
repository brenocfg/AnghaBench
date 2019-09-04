#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 char* setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

void getOSCharset(char *locale, const size_t size) {
    char * codec = NULL;
    size_t cur = 0;
    short flag = 0;
    setlocale(LC_CTYPE, "");
    codec = setlocale(LC_CTYPE, NULL);
    // get codeset from language[_territory][.codeset][@modifier]
    while (*codec) {
        if (!flag) {
            if (*codec != '.') {
                codec++;
                continue;
            } else {
                flag = 1;
                codec++;
            }
        } else {
            if (*codec == '@') {
                break;
            } else {
                locale[cur++] = (*codec);
                codec++;
                if (cur >= size) {
                    // Not enough size
                    cur = 0;
                    break;
                }
            }
        }
    }
    locale[cur] = '\0';
    if (!strlen(locale)) {
        strcpy(locale, "8859_1");
    }
    return;
}