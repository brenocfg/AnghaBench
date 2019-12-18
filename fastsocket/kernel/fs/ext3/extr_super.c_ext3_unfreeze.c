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
struct TYPE_2__ {int /*<<< orphan*/  s_journal; int /*<<< orphan*/  s_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT3_FEATURE_INCOMPAT_RECOVER ; 
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT3_SET_INCOMPAT_FEATURE (struct super_block*,int /*<<< orphan*/ ) ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  ext3_commit_super (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  journal_unlock_updates (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static int ext3_unfreeze(struct super_block *sb)
{
	if (!(sb->s_flags & MS_RDONLY)) {
		lock_super(sb);
		/* Reser the needs_recovery flag before the fs is unlocked. */
		EXT3_SET_INCOMPAT_FEATURE(sb, EXT3_FEATURE_INCOMPAT_RECOVER);
		ext3_commit_super(sb, EXT3_SB(sb)->s_es, 1);
		unlock_super(sb);
		journal_unlock_updates(EXT3_SB(sb)->s_journal);
	}
	return 0;
}