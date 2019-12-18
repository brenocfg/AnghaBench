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
struct TYPE_3__ {char* name; int /*<<< orphan*/  fd; int /*<<< orphan*/  status; int /*<<< orphan*/  dir; scalar_t__ f; } ;
typedef  TYPE_1__ Test ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int WEXITSTATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFEXITED (int /*<<< orphan*/ ) ; 
 scalar_t__ WIFSIGNALED (int /*<<< orphan*/ ) ; 
 int WTERMSIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyfd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ failed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  rmtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
report(Test *t)
{
    int nfail = 0, nerr = 0;

    putchar('\n');
    for (; t->f; t++) {
        rmtree(t->dir);
        if (!t->status) {
            continue;
        }

        printf("\n%s: ", t->name);
        if (failed(t->status)) {
            nfail++;
            printf("failure");
        } else {
            nerr++;
            printf("error");
            if (WIFEXITED(t->status)) {
                printf(" (exit status %d)", WEXITSTATUS(t->status));
            }
            if (WIFSIGNALED(t->status)) {
                printf(" (signal %d)", WTERMSIG(t->status));
            }
        }

        putchar('\n');
        lseek(t->fd, 0, SEEK_SET);
        copyfd(stdout, t->fd);
    }

    if (nfail || nerr) {
        printf("\n%d failures; %d errors.\n", nfail, nerr);
    } else {
        printf("\nPASS\n");
    }
    return nfail || nerr;
}