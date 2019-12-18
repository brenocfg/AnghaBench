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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {int max_slots; int slot_num; int /*<<< orphan*/  osb_lock; int /*<<< orphan*/ * slot_recovery_generations; } ;
struct ocfs2_dinode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOENT ; 
 scalar_t__ __ocfs2_recovery_map_test (struct ocfs2_super*,unsigned int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_get_recovery_generation (struct ocfs2_dinode*) ; 
 int ocfs2_read_journal_inode (struct ocfs2_super*,int,struct buffer_head**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_recovery_thread (struct ocfs2_super*,unsigned int) ; 
 int ocfs2_slot_to_node_num_locked (struct ocfs2_super*,int,unsigned int*) ; 
 int ocfs2_trylock_journal (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ocfs2_mark_dead_nodes(struct ocfs2_super *osb)
{
	unsigned int node_num;
	int status, i;
	u32 gen;
	struct buffer_head *bh = NULL;
	struct ocfs2_dinode *di;

	/* This is called with the super block cluster lock, so we
	 * know that the slot map can't change underneath us. */

	for (i = 0; i < osb->max_slots; i++) {
		/* Read journal inode to get the recovery generation */
		status = ocfs2_read_journal_inode(osb, i, &bh, NULL);
		if (status) {
			mlog_errno(status);
			goto bail;
		}
		di = (struct ocfs2_dinode *)bh->b_data;
		gen = ocfs2_get_recovery_generation(di);
		brelse(bh);
		bh = NULL;

		spin_lock(&osb->osb_lock);
		osb->slot_recovery_generations[i] = gen;

		mlog(0, "Slot %u recovery generation is %u\n", i,
		     osb->slot_recovery_generations[i]);

		if (i == osb->slot_num) {
			spin_unlock(&osb->osb_lock);
			continue;
		}

		status = ocfs2_slot_to_node_num_locked(osb, i, &node_num);
		if (status == -ENOENT) {
			spin_unlock(&osb->osb_lock);
			continue;
		}

		if (__ocfs2_recovery_map_test(osb, node_num)) {
			spin_unlock(&osb->osb_lock);
			continue;
		}
		spin_unlock(&osb->osb_lock);

		/* Ok, we have a slot occupied by another node which
		 * is not in the recovery map. We trylock his journal
		 * file here to test if he's alive. */
		status = ocfs2_trylock_journal(osb, i);
		if (!status) {
			/* Since we're called from mount, we know that
			 * the recovery thread can't race us on
			 * setting / checking the recovery bits. */
			ocfs2_recovery_thread(osb, node_num);
		} else if ((status < 0) && (status != -EAGAIN)) {
			mlog_errno(status);
			goto bail;
		}
	}

	status = 0;
bail:
	mlog_exit(status);
	return status;
}