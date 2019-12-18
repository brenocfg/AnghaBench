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
struct buffer_head {scalar_t__ b_blocknr; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ML_ERROR ; 
 int jbd2_journal_dirty_metadata (int /*<<< orphan*/ *,struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_entry (char*,unsigned long long) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 

int ocfs2_journal_dirty(handle_t *handle,
			struct buffer_head *bh)
{
	int status;

	mlog_entry("(bh->b_blocknr=%llu)\n",
		   (unsigned long long)bh->b_blocknr);

	status = jbd2_journal_dirty_metadata(handle, bh);
	if (status < 0)
		mlog(ML_ERROR, "Could not dirty metadata buffer. "
		     "(bh->b_blocknr=%llu)\n",
		     (unsigned long long)bh->b_blocknr);

	mlog_exit(status);
	return status;
}