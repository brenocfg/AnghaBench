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
struct ocfs2_super {int /*<<< orphan*/  osb_lock; int /*<<< orphan*/ * osb_orphan_wipes; int /*<<< orphan*/  osb_recovering_orphan_dirs; } ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ocfs2_node_map_test_bit (struct ocfs2_super*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_check_orphan_recovery_state(struct ocfs2_super *osb,
					     int slot)
{
	int ret = 0;

	spin_lock(&osb->osb_lock);
	if (ocfs2_node_map_test_bit(osb, &osb->osb_recovering_orphan_dirs, slot)) {
		mlog(0, "Recovery is happening on orphan dir %d, will skip "
		     "this inode\n", slot);
		ret = -EDEADLK;
		goto out;
	}
	/* This signals to the orphan recovery process that it should
	 * wait for us to handle the wipe. */
	osb->osb_orphan_wipes[slot]++;
out:
	spin_unlock(&osb->osb_lock);
	return ret;
}