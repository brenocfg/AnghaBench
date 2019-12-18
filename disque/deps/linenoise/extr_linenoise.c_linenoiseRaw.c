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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  disableRawMode (int /*<<< orphan*/ ) ; 
 int enableRawMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fgets (char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int linenoiseEdit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,char const*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

__attribute__((used)) static int linenoiseRaw(char *buf, size_t buflen, const char *prompt) {
    int count;

    if (buflen == 0) {
        errno = EINVAL;
        return -1;
    }
    if (!isatty(STDIN_FILENO)) {
        /* Not a tty: read from file / pipe. */
        if (fgets(buf, buflen, stdin) == NULL) return -1;
        count = strlen(buf);
        if (count && buf[count-1] == '\n') {
            count--;
            buf[count] = '\0';
        }
    } else {
        /* Interactive editing. */
        if (enableRawMode(STDIN_FILENO) == -1) return -1;
        count = linenoiseEdit(STDIN_FILENO, STDOUT_FILENO, buf, buflen, prompt);
        disableRawMode(STDIN_FILENO);
        printf("\n");
    }
    return count;
}