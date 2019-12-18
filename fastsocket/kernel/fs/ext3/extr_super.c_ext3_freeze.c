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
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_es; int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_CLEAR_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT3_FEATURE_INCOMPAT_RECOVER ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int MS_RDONLY ; 
 int ext3_commit_super (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int journal_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_lock_updates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  journal_unlock_updates (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext3_freeze(struct super_block *sb)
{
	int error = 0;
	journal_t *journal;

	if (!(sb->s_flags & MS_RDONLY)) {
		journal = EXT3_SB(sb)->s_journal;

		/* Now we set up the journal barrier. */
		journal_lock_updates(journal);

		/*
		 * We don't want to clear needs_recovery flag when we failed
		 * to flush the journal.
		 */
		error = journal_flush(journal);
		if (error < 0)
			goto out;

		/* Journal blocked and flushed, clear needs_recovery flag. */
		EXT3_CLEAR_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_RECOVER);
		error = ext3_commit_super(sb, EXT3_SB(sb)->s_es, 1);
		if (error)
			goto out;
	}
	return 0;

out:
	journal_unlock_updates(journal);
	return error;
}