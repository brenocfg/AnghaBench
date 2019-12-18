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
 int isinferior (scalar_t__,scalar_t__) ; 
 scalar_t__ proc_find (int) ; 
 int /*<<< orphan*/  proc_rele (scalar_t__) ; 

int
proc_isinferior(int pid1, int pid2)
{
	proc_t p = PROC_NULL;
	proc_t t = PROC_NULL;
	int retval = 0;
	
	if (((p = proc_find(pid1)) != (proc_t)0 ) && ((t = proc_find(pid2)) != (proc_t)0))
		retval = isinferior(p, t);

	if (p != PROC_NULL)
		proc_rele(p);
	if (t != PROC_NULL)
		proc_rele(t);

	return(retval);
}