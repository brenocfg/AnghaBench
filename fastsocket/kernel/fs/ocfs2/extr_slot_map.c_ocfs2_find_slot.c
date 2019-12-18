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
struct ocfs2_super {int slot_num; int /*<<< orphan*/  osb_lock; int /*<<< orphan*/  node_num; int /*<<< orphan*/  preferred_slot; struct ocfs2_slot_info* slot_info; } ;
struct ocfs2_slot_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int __ocfs2_find_empty_slot (struct ocfs2_slot_info*,int /*<<< orphan*/ ) ; 
 int __ocfs2_node_num_to_slot (struct ocfs2_slot_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_set_slot (struct ocfs2_slot_info*,int,int /*<<< orphan*/ ) ; 
 int ocfs2_update_disk_slot (struct ocfs2_super*,struct ocfs2_slot_info*,int) ; 
 int /*<<< orphan*/  ocfs2_update_slot_info (struct ocfs2_slot_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_find_slot(struct ocfs2_super *osb)
{
	int status;
	int slot;
	struct ocfs2_slot_info *si;

	mlog_entry_void();

	si = osb->slot_info;

	spin_lock(&osb->osb_lock);
	ocfs2_update_slot_info(si);

	/* search for ourselves first and take the slot if it already
	 * exists. Perhaps we need to mark this in a variable for our
	 * own journal recovery? Possibly not, though we certainly
	 * need to warn to the user */
	slot = __ocfs2_node_num_to_slot(si, osb->node_num);
	if (slot < 0) {
		/* if no slot yet, then just take 1st available
		 * one. */
		slot = __ocfs2_find_empty_slot(si, osb->preferred_slot);
		if (slot < 0) {
			spin_unlock(&osb->osb_lock);
			mlog(ML_ERROR, "no free slots available!\n");
			status = -EINVAL;
			goto bail;
		}
	} else
		mlog(ML_NOTICE, "slot %d is already allocated to this node!\n",
		     slot);

	ocfs2_set_slot(si, slot, osb->node_num);
	osb->slot_num = slot;
	spin_unlock(&osb->osb_lock);

	mlog(0, "taking node slot %d\n", osb->slot_num);

	status = ocfs2_update_disk_slot(osb, si, osb->slot_num);
	if (status < 0)
		mlog_errno(status);

bail:
	mlog_exit(status);
	return status;
}