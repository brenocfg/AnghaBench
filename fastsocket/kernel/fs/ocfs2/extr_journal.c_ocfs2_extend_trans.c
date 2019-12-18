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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int jbd2_journal_extend (int /*<<< orphan*/ *,int) ; 
 int jbd2_journal_restart (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 

int ocfs2_extend_trans(handle_t *handle, int nblocks)
{
	int status;

	BUG_ON(!handle);
	BUG_ON(!nblocks);

	mlog_entry_void();

	mlog(0, "Trying to extend transaction by %d blocks\n", nblocks);

#ifdef CONFIG_OCFS2_DEBUG_FS
	status = 1;
#else
	status = jbd2_journal_extend(handle, nblocks);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
#endif

	if (status > 0) {
		mlog(0,
		     "jbd2_journal_extend failed, trying "
		     "jbd2_journal_restart\n");
		status = jbd2_journal_restart(handle, nblocks);
		if (status < 0) {
			mlog_errno(status);
			goto bail;
		}
	}

	status = 0;
bail:

	mlog_exit(status);
	return status;
}