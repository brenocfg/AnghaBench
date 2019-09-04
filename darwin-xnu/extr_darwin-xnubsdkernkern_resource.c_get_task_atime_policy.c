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
struct proc {int p_vfs_iopolicy; } ;

/* Variables and functions */
 int IOPOL_ATIME_UPDATES_DEFAULT ; 
 int IOPOL_ATIME_UPDATES_OFF ; 
 int P_VFS_IOPOLICY_ATIME_UPDATES ; 

__attribute__((used)) static inline int
get_task_atime_policy(struct proc *p)
{
	return (p->p_vfs_iopolicy & P_VFS_IOPOLICY_ATIME_UPDATES)? IOPOL_ATIME_UPDATES_OFF: IOPOL_ATIME_UPDATES_DEFAULT;
}