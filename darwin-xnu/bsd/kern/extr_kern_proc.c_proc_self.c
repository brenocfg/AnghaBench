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
struct proc {int dummy; } ;
typedef  struct proc* proc_t ;

/* Variables and functions */
 struct proc* PROC_NULL ; 
 struct proc* current_proc () ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 struct proc* proc_ref_locked (struct proc*) ; 

proc_t
proc_self(void)
{
	struct proc * p;

	p = current_proc();

	proc_list_lock();
	if (p != proc_ref_locked(p))
		p = PROC_NULL;
	proc_list_unlock();
	return(p);
}