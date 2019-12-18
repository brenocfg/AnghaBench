#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* proc_t ;
struct TYPE_4__ {scalar_t__ p_pid; struct TYPE_4__* p_pptr; } ;

/* Variables and functions */
 int nprocs ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 

int
isinferior(proc_t p, proc_t t)
{
	int retval = 0;
	int nchecked = 0;
	proc_t start = p;

	/* if p==t they are not inferior */
	if (p == t)
		return(0);

	proc_list_lock();
	for (; p != t; p = p->p_pptr) {
		nchecked++;

		/* Detect here if we're in a cycle */
		if ((p->p_pid == 0) || (p->p_pptr == start) || (nchecked >= nprocs))
			goto out;
	}
	retval = 1;
out:
	proc_list_unlock();
	return(retval);
}