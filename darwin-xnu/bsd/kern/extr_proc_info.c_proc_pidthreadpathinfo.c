#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * vip_path; int /*<<< orphan*/  vip_vi; } ;
struct proc_threadwithpathinfo {TYPE_1__ pvip; int /*<<< orphan*/  pt; } ;
struct proc_threadinfo_internal {int dummy; } ;
typedef  TYPE_2__* proc_t ;
struct TYPE_5__ {int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int ESRCH ; 
 int MAXPATHLEN ; 
 scalar_t__ NULLVP ; 
 int /*<<< orphan*/  bzero (struct proc_threadwithpathinfo*,int) ; 
 int fill_taskthreadinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc_threadinfo_internal*,void*,int*) ; 
 int fill_vnodeinfo (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vn_getpath (scalar_t__,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ vnode_getwithvid (scalar_t__,int) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 

int 
proc_pidthreadpathinfo(proc_t p, uint64_t arg,  struct proc_threadwithpathinfo *pinfo)
{
	vnode_t vp = NULLVP;
	int vid;
	int error = 0;
	uint64_t threadaddr = (uint64_t)arg;
	int count;

	bzero(pinfo, sizeof(struct proc_threadwithpathinfo));

	error = fill_taskthreadinfo(p->task, threadaddr, 0, (struct proc_threadinfo_internal *)&pinfo->pt, (void *)&vp, &vid);
	if (error)
		return(ESRCH);

	if ((vp != NULLVP) && ((vnode_getwithvid(vp, vid)) == 0)) {
		error = fill_vnodeinfo(vp, &pinfo->pvip.vip_vi) ;
		if (error == 0) {
			count = MAXPATHLEN;
			vn_getpath(vp, &pinfo->pvip.vip_path[0], &count);
			pinfo->pvip.vip_path[MAXPATHLEN-1] = 0;
		}
		vnode_put(vp);
	}	
	return(error);
}