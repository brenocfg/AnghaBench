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
 int /*<<< orphan*/  LINENOISE_MAX_LINE ; 
 char* calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumbmode ; 
 int /*<<< orphan*/  free (char*) ; 
 int linenoiseDumb (char*,int /*<<< orphan*/ ,char const*) ; 
 int linenoiseRaw (char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sanitize (char*) ; 
 int strlen (char*) ; 

char *linenoise(const char *prompt) {
    char *buf = calloc(1, LINENOISE_MAX_LINE);
    int count = 0;
    if (!dumbmode) {
        count = linenoiseRaw(buf, LINENOISE_MAX_LINE, prompt);
    } else {
        count = linenoiseDumb(buf, LINENOISE_MAX_LINE, prompt);
    }
    if (count > 0) {
        sanitize(buf);
        count = strlen(buf);
    }
    if (count <= 0) {
        free(buf);
        return NULL;
    }
    return buf;
}