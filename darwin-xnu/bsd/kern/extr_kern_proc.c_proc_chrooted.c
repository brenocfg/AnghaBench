#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* proc_t ;
struct TYPE_7__ {TYPE_1__* p_fd; } ;
struct TYPE_6__ {int /*<<< orphan*/ * fd_rdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_fdlock (TYPE_2__*) ; 
 int /*<<< orphan*/  proc_fdunlock (TYPE_2__*) ; 

int
proc_chrooted(proc_t p)
{
	int retval = 0;

	if (p) {
		proc_fdlock(p);
		retval = (p->p_fd->fd_rdir != NULL) ? 1 : 0;
		proc_fdunlock(p);
	}

	return retval;
}