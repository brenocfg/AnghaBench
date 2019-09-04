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
 int LINENOISE_MAX_LINE ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ isUnsupportedTerm () ; 
 int linenoiseRaw (char*,int,char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 char* strdup (char*) ; 
 size_t strlen (char*) ; 

char *linenoise(const char *prompt) {
    char buf[LINENOISE_MAX_LINE];
    int count;

    if (isUnsupportedTerm()) {
        size_t len;

        printf("%s",prompt);
        fflush(stdout);
        if (fgets(buf,LINENOISE_MAX_LINE,stdin) == NULL) return NULL;
        len = strlen(buf);
        while(len && (buf[len-1] == '\n' || buf[len-1] == '\r')) {
            len--;
            buf[len] = '\0';
        }
        return strdup(buf);
    } else {
        count = linenoiseRaw(buf,LINENOISE_MAX_LINE,prompt);
        if (count == -1) return NULL;
        return strdup(buf);
    }
}