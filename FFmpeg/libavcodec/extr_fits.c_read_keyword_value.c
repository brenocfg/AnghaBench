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
typedef  char uint8_t ;

/* Variables and functions */

__attribute__((used)) static int read_keyword_value(const uint8_t *ptr8, char *keyword, char *value)
{
    int i;

    for (i = 0; i < 8 && ptr8[i] != ' '; i++) {
        keyword[i] = ptr8[i];
    }
    keyword[i] = '\0';

    if (ptr8[8] == '=') {
        i = 10;
        while (i < 80 && ptr8[i] == ' ') {
            i++;
        }

        if (i < 80) {
            *value++ = ptr8[i];
            i++;
            if (ptr8[i-1] == '\'') {
                for (; i < 80 && ptr8[i] != '\''; i++) {
                    *value++ = ptr8[i];
                }
                *value++ = '\'';
            } else if (ptr8[i-1] == '(') {
                for (; i < 80 && ptr8[i] != ')'; i++) {
                    *value++ = ptr8[i];
                }
                *value++ = ')';
            } else {
                for (; i < 80 && ptr8[i] != ' ' && ptr8[i] != '/'; i++) {
                    *value++ = ptr8[i];
                }
            }
        }
    }
    *value = '\0';
    return 0;
}