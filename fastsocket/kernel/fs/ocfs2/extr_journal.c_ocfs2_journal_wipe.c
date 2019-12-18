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
struct ocfs2_journal {int /*<<< orphan*/  j_osb; int /*<<< orphan*/  j_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int jbd2_journal_wipe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_journal_toggle_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ocfs2_journal_wipe(struct ocfs2_journal *journal, int full)
{
	int status;

	mlog_entry_void();

	BUG_ON(!journal);

	status = jbd2_journal_wipe(journal->j_journal, full);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

	status = ocfs2_journal_toggle_dirty(journal->j_osb, 0, 0);
	if (status < 0)
		mlog_errno(status);

bail:
	mlog_exit(status);
	return status;
}