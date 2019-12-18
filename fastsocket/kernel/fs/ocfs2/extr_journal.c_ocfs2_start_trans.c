#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ocfs2_super {TYPE_1__* journal; int /*<<< orphan*/  sb; } ;
typedef  int /*<<< orphan*/  journal_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {scalar_t__ j_state; int /*<<< orphan*/  j_num_trans; int /*<<< orphan*/  j_trans_barrier; int /*<<< orphan*/ * j_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EROFS ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ OCFS2_JOURNAL_FREE ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 scalar_t__ is_journal_aborted (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jbd2_journal_start (int /*<<< orphan*/ *,int) ; 
 scalar_t__ journal_current_handle () ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_abort (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ocfs2_is_hard_readonly (struct ocfs2_super*) ; 
 int /*<<< orphan*/  ocfs2_mount_local (struct ocfs2_super*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

handle_t *ocfs2_start_trans(struct ocfs2_super *osb, int max_buffs)
{
	journal_t *journal = osb->journal->j_journal;
	handle_t *handle;

	BUG_ON(!osb || !osb->journal->j_journal);

	if (ocfs2_is_hard_readonly(osb))
		return ERR_PTR(-EROFS);

	BUG_ON(osb->journal->j_state == OCFS2_JOURNAL_FREE);
	BUG_ON(max_buffs <= 0);

	/* Nested transaction? Just return the handle... */
	if (journal_current_handle())
		return jbd2_journal_start(journal, max_buffs);

	down_read(&osb->journal->j_trans_barrier);

	handle = jbd2_journal_start(journal, max_buffs);
	if (IS_ERR(handle)) {
		up_read(&osb->journal->j_trans_barrier);

		mlog_errno(PTR_ERR(handle));

		if (is_journal_aborted(journal)) {
			ocfs2_abort(osb->sb, "Detected aborted journal");
			handle = ERR_PTR(-EROFS);
		}
	} else {
		if (!ocfs2_mount_local(osb))
			atomic_inc(&(osb->journal->j_num_trans));
	}

	return handle;
}