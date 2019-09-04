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
struct proc_workqueueinfo {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  bzero (struct proc_workqueueinfo*,int) ; 
 int fill_procworkqueue (int /*<<< orphan*/ ,struct proc_workqueueinfo*) ; 

int 
proc_pidworkqueueinfo(proc_t p, struct proc_workqueueinfo *pwqinfo)
{
	int error = 0;

	bzero(pwqinfo, sizeof(struct proc_workqueueinfo));

	error = fill_procworkqueue(p, pwqinfo);
	if (error)
		return(ESRCH);
	else
		return(0);

}