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
typedef  int /*<<< orphan*/  uint64_t ;
struct proc_threadinfo_internal {int dummy; } ;
struct proc_threadinfo {int dummy; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  bzero (struct proc_threadinfo*,int) ; 
 int fill_taskthreadinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct proc_threadinfo_internal*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int 
proc_pidthreadinfo(proc_t p, uint64_t arg, bool thuniqueid, struct proc_threadinfo *pthinfo)
{
	int error = 0;
	uint64_t threadaddr = (uint64_t)arg;

	bzero(pthinfo, sizeof(struct proc_threadinfo));

	error = fill_taskthreadinfo(p->task, threadaddr, thuniqueid, (struct proc_threadinfo_internal *)pthinfo, NULL, NULL);
	if (error)
		return(ESRCH);
	else
		return(0);

}