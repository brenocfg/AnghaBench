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
typedef  scalar_t__ proc_t ;

/* Variables and functions */
 scalar_t__ PROC_NULL ; 
 scalar_t__ pfind_locked (int) ; 
 int /*<<< orphan*/  proc_list_lock () ; 
 int /*<<< orphan*/  proc_list_unlock () ; 
 scalar_t__ proc_ref_locked (scalar_t__) ; 

proc_t
proc_findinternal(int pid, int locked)
{
	proc_t p = PROC_NULL;

	if (locked == 0) {
		proc_list_lock();
	}

	p = pfind_locked(pid);
	if ((p == PROC_NULL) || (p != proc_ref_locked(p)))
		p = PROC_NULL;

	if (locked == 0) {
		proc_list_unlock();
	}

	return(p);
}