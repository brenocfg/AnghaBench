#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct ext3_sb_info {scalar_t__ s_commit_interval; } ;
struct TYPE_3__ {int /*<<< orphan*/  j_state_lock; int /*<<< orphan*/  j_flags; scalar_t__ j_commit_interval; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 int /*<<< orphan*/  DATA_ERR_ABORT ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  JFS_ABORT_ON_SYNCDATA_ERR ; 
 int /*<<< orphan*/  JFS_BARRIER ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext3_init_journal_params(struct super_block *sb, journal_t *journal)
{
	struct ext3_sb_info *sbi = EXT3_SB(sb);

	if (sbi->s_commit_interval)
		journal->j_commit_interval = sbi->s_commit_interval;
	/* We could also set up an ext3-specific default for the commit
	 * interval here, but for now we'll just fall back to the jbd
	 * default. */

	spin_lock(&journal->j_state_lock);
	if (test_opt(sb, BARRIER))
		journal->j_flags |= JFS_BARRIER;
	else
		journal->j_flags &= ~JFS_BARRIER;
	if (test_opt(sb, DATA_ERR_ABORT))
		journal->j_flags |= JFS_ABORT_ON_SYNCDATA_ERR;
	else
		journal->j_flags &= ~JFS_ABORT_ON_SYNCDATA_ERR;
	spin_unlock(&journal->j_state_lock);
}