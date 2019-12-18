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
typedef  int /*<<< orphan*/  uint16_t ;
struct proc {int /*<<< orphan*/  p_vfs_iopolicy; } ;

/* Variables and functions */
 int IOPOL_ATIME_UPDATES_OFF ; 
 int /*<<< orphan*/  OSBitAndAtomic16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSBitOrAtomic16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ P_VFS_IOPOLICY_ATIME_UPDATES ; 

__attribute__((used)) static inline void
set_task_atime_policy(struct proc *p, int policy)
{
	if (policy == IOPOL_ATIME_UPDATES_OFF) {
		OSBitOrAtomic16((uint16_t)P_VFS_IOPOLICY_ATIME_UPDATES, &p->p_vfs_iopolicy);
	} else {
		OSBitAndAtomic16(~((uint16_t)P_VFS_IOPOLICY_ATIME_UPDATES), &p->p_vfs_iopolicy);
	}
}