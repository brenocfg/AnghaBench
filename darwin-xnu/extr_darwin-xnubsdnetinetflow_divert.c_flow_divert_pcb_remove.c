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
struct flow_divert_pcb {struct flow_divert_group* group; int /*<<< orphan*/  ref_count; } ;
struct flow_divert_group {int /*<<< orphan*/  lck; int /*<<< orphan*/  pcb_tree; int /*<<< orphan*/  ctl_unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDLOG (int /*<<< orphan*/ ,struct flow_divert_pcb*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FDRELEASE (struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct flow_divert_pcb*) ; 
 int /*<<< orphan*/  fd_pcb_tree ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
flow_divert_pcb_remove(struct flow_divert_pcb *fd_cb)
{
	if (fd_cb->group != NULL) {
		struct flow_divert_group *group = fd_cb->group;
		lck_rw_lock_exclusive(&group->lck);
		FDLOG(LOG_INFO, fd_cb, "Removing from group %d, ref count = %d", group->ctl_unit, fd_cb->ref_count);
		RB_REMOVE(fd_pcb_tree, &group->pcb_tree, fd_cb);
		fd_cb->group = NULL;
		FDRELEASE(fd_cb);				/* Release the group's reference */
		lck_rw_done(&group->lck);
	}
}