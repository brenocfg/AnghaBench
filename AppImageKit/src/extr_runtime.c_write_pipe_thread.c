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
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  fuse_pid ; 
 int /*<<< orphan*/ * keepalive_pipe ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void *
write_pipe_thread (void *arg)
{
    char c[32];
    int res;
    //  sprintf(stderr, "Called write_pipe_thread");
    memset (c, 'x', sizeof (c));
    while (1) {
        /* Write until we block, on broken pipe, exit */
        res = write (keepalive_pipe[1], c, sizeof (c));
        if (res == -1) {
            kill (fuse_pid, SIGTERM);
            break;
        }
    }
    return NULL;
}