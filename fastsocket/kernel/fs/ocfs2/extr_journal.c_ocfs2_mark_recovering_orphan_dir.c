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
struct ocfs2_super {int /*<<< orphan*/  osb_lock; int /*<<< orphan*/  osb_wipe_event; scalar_t__* osb_orphan_wipes; int /*<<< orphan*/  osb_recovering_orphan_dirs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ocfs2_node_map_set_bit (struct ocfs2_super*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocfs2_orphan_recovery_can_continue (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_mark_recovering_orphan_dir(struct ocfs2_super *osb,
					     int slot)
{
	spin_lock(&osb->osb_lock);
	/* Mark ourselves such that new processes in delete_inode()
	 * know to quit early. */
	ocfs2_node_map_set_bit(osb, &osb->osb_recovering_orphan_dirs, slot);
	while (osb->osb_orphan_wipes[slot]) {
		/* If any processes are already in the middle of an
		 * orphan wipe on this dir, then we need to wait for
		 * them. */
		spin_unlock(&osb->osb_lock);
		wait_event_interruptible(osb->osb_wipe_event,
					 ocfs2_orphan_recovery_can_continue(osb, slot));
		spin_lock(&osb->osb_lock);
	}
	spin_unlock(&osb->osb_lock);
}