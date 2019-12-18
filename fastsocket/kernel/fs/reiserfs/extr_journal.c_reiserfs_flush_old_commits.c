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
typedef  scalar_t__ time_t ;
struct super_block {int s_dirt; } ;
struct reiserfs_transaction_handle {int dummy; } ;
struct reiserfs_journal {scalar_t__ j_trans_start_time; scalar_t__ j_len; scalar_t__ j_max_trans_age; int /*<<< orphan*/  j_wcount; int /*<<< orphan*/  j_journal_list; } ;

/* Variables and functions */
 int COMMIT_NOW ; 
 int /*<<< orphan*/  SB_BUFFER_WITH_SB (struct super_block*) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int WAIT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_journal_end (struct reiserfs_transaction_handle*,struct super_block*,int,int) ; 
 scalar_t__ get_seconds () ; 
 int /*<<< orphan*/  journal_join (struct reiserfs_transaction_handle*,struct super_block*,int) ; 
 int /*<<< orphan*/  journal_mark_dirty (struct reiserfs_transaction_handle*,struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reiserfs_prepare_for_journal (struct super_block*,int /*<<< orphan*/ ,int) ; 

int reiserfs_flush_old_commits(struct super_block *sb)
{
	time_t now;
	struct reiserfs_transaction_handle th;
	struct reiserfs_journal *journal = SB_JOURNAL(sb);

	now = get_seconds();
	/* safety check so we don't flush while we are replaying the log during
	 * mount
	 */
	if (list_empty(&journal->j_journal_list)) {
		return 0;
	}

	/* check the current transaction.  If there are no writers, and it is
	 * too old, finish it, and force the commit blocks to disk
	 */
	if (atomic_read(&journal->j_wcount) <= 0 &&
	    journal->j_trans_start_time > 0 &&
	    journal->j_len > 0 &&
	    (now - journal->j_trans_start_time) > journal->j_max_trans_age) {
		if (!journal_join(&th, sb, 1)) {
			reiserfs_prepare_for_journal(sb,
						     SB_BUFFER_WITH_SB(sb),
						     1);
			journal_mark_dirty(&th, sb,
					   SB_BUFFER_WITH_SB(sb));

			/* we're only being called from kreiserfsd, it makes no sense to do
			 ** an async commit so that kreiserfsd can do it later
			 */
			do_journal_end(&th, sb, 1, COMMIT_NOW | WAIT);
		}
	}
	return sb->s_dirt;
}