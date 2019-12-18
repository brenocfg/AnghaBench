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
struct ocfs2_super {int node_num; int /*<<< orphan*/  journal; } ;
struct ocfs2_dinode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  mlog_entry (char*,int,int,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_begin_local_alloc_recovery (struct ocfs2_super*,int,struct ocfs2_dinode**) ; 
 int ocfs2_begin_truncate_log_recovery (struct ocfs2_super*,int,struct ocfs2_dinode**) ; 
 int ocfs2_clear_slot (struct ocfs2_super*,int) ; 
 int /*<<< orphan*/  ocfs2_queue_recovery_completion (int /*<<< orphan*/ ,int,struct ocfs2_dinode*,struct ocfs2_dinode*,int /*<<< orphan*/ *) ; 
 int ocfs2_replay_journal (struct ocfs2_super*,int,int) ; 

__attribute__((used)) static int ocfs2_recover_node(struct ocfs2_super *osb,
			      int node_num, int slot_num)
{
	int status = 0;
	struct ocfs2_dinode *la_copy = NULL;
	struct ocfs2_dinode *tl_copy = NULL;

	mlog_entry("(node_num=%d, slot_num=%d, osb->node_num = %d)\n",
		   node_num, slot_num, osb->node_num);

	/* Should not ever be called to recover ourselves -- in that
	 * case we should've called ocfs2_journal_load instead. */
	BUG_ON(osb->node_num == node_num);

	status = ocfs2_replay_journal(osb, node_num, slot_num);
	if (status < 0) {
		if (status == -EBUSY) {
			mlog(0, "Skipping recovery for slot %u (node %u) "
			     "as another node has recovered it\n", slot_num,
			     node_num);
			status = 0;
			goto done;
		}
		mlog_errno(status);
		goto done;
	}

	/* Stamp a clean local alloc file AFTER recovering the journal... */
	status = ocfs2_begin_local_alloc_recovery(osb, slot_num, &la_copy);
	if (status < 0) {
		mlog_errno(status);
		goto done;
	}

	/* An error from begin_truncate_log_recovery is not
	 * serious enough to warrant halting the rest of
	 * recovery. */
	status = ocfs2_begin_truncate_log_recovery(osb, slot_num, &tl_copy);
	if (status < 0)
		mlog_errno(status);

	/* Likewise, this would be a strange but ultimately not so
	 * harmful place to get an error... */
	status = ocfs2_clear_slot(osb, slot_num);
	if (status < 0)
		mlog_errno(status);

	/* This will kfree the memory pointed to by la_copy and tl_copy */
	ocfs2_queue_recovery_completion(osb->journal, slot_num, la_copy,
					tl_copy, NULL);

	status = 0;
done:

	mlog_exit(status);
	return status;
}