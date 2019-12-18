#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int pid; int status; scalar_t__ f; } ;
typedef  TYPE_1__ Test ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  die (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ failed (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  killpg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  stdout ; 
 int wait3 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
waittest(Test *ts)
{
    Test *t;
    int pid, stat;

    pid = wait3(&stat, 0, 0);
    if (pid == -1) {
        die(3, errno, "wait");
    }
    killpg(pid, SIGKILL);

    for (t=ts; t->f; t++) {
        if (t->pid == pid) {
            t->status = stat;
            if (!t->status) {
                putchar('.');
            } else if (failed(t->status)) {
                putchar('F');
            } else {
                putchar('E');
            }
            fflush(stdout);
        }
    }
}