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
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usleep (int) ; 

int linenoiseProbe(void) {
    /* Switch to non-blocking mode */
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    int res = fcntl(STDIN_FILENO, F_SETFL, flags);
    if (res != 0) {
        return -1;
    }
    /* Device status request */
    fprintf(stdout, "\x1b[5n");

    /* Try to read response */
    int timeout_ms = 200;
    size_t read_bytes = 0;
    while (timeout_ms > 0 && read_bytes < 4) { // response is ESC[0n or ESC[3n
        usleep(10000);
        char c;
        int cb = fread(&c, 1, 1, stdin);
        read_bytes += cb;
        timeout_ms--;
    }
    /* Restore old mode */
    flags &= ~O_NONBLOCK;
    res = fcntl(STDIN_FILENO, F_SETFL, flags);
    if (res != 0) {
        return -1;
    }
    if (read_bytes < 4) {
        return -2;
    }
    return 0;
}