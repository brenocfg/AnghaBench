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
struct super_block {int s_flags; } ;
struct ext3_super_block {int dummy; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_CLEAR_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT3_FEATURE_INCOMPAT_RECOVER ; 
 scalar_t__ EXT3_HAS_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  ext3_commit_super (struct super_block*,struct ext3_super_block*,int) ; 
 scalar_t__ journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_unlock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static void ext3_mark_recovery_complete(struct super_block * sb,
					struct ext3_super_block * es)
{
	journal_t *journal = EXT3_SB(sb)->s_journal;

	journal_lock_updates(journal);
	if (journal_flush(journal) < 0)
		goto out;

	lock_super(sb);
	if (EXT3_HAS_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_RECOVER) &&
	    sb->s_flags & MS_RDONLY) {
		EXT3_CLEAR_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_RECOVER);
		ext3_commit_super(sb, es, 1);
	}
	unlock_super(sb);

out:
	journal_unlock_updates(journal);
}