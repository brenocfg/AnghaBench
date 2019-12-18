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
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int linenoiseEdit (char*,size_t,char const*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int linenoiseRaw(char *buf, size_t buflen, const char *prompt) {
    int count;

    if (buflen == 0) {
        errno = EINVAL;
        return -1;
    }

    count = linenoiseEdit(buf, buflen, prompt);
    fputc('\n', stdout);
    return count;
}