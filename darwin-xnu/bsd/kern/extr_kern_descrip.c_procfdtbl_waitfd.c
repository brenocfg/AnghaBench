#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct proc {int /*<<< orphan*/  p_fdmlock; TYPE_1__* p_fd; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fd_ofileflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  UF_RESVWAIT ; 
 int /*<<< orphan*/  msleep (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
procfdtbl_waitfd(struct proc * p, int fd)
{
        p->p_fd->fd_ofileflags[fd] |= UF_RESVWAIT;
	msleep(&p->p_fd, &p->p_fdmlock, PRIBIO, "ftbl_waitfd", NULL);
}