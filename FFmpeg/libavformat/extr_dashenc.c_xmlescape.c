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
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_realloc (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *xmlescape(const char *str) {
    int outlen = strlen(str)*3/2 + 6;
    char *out = av_realloc(NULL, outlen + 1);
    int pos = 0;
    if (!out)
        return NULL;
    for (; *str; str++) {
        if (pos + 6 > outlen) {
            char *tmp;
            outlen = 2 * outlen + 6;
            tmp = av_realloc(out, outlen + 1);
            if (!tmp) {
                av_free(out);
                return NULL;
            }
            out = tmp;
        }
        if (*str == '&') {
            memcpy(&out[pos], "&amp;", 5);
            pos += 5;
        } else if (*str == '<') {
            memcpy(&out[pos], "&lt;", 4);
            pos += 4;
        } else if (*str == '>') {
            memcpy(&out[pos], "&gt;", 4);
            pos += 4;
        } else if (*str == '\'') {
            memcpy(&out[pos], "&apos;", 6);
            pos += 6;
        } else if (*str == '\"') {
            memcpy(&out[pos], "&quot;", 6);
            pos += 6;
        } else {
            out[pos++] = *str;
        }
    }
    out[pos] = '\0';
    return out;
}