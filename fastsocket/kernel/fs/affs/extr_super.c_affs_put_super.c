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
struct super_block {int s_flags; int /*<<< orphan*/ * s_fs_info; } ;
struct affs_sb_info {int /*<<< orphan*/  s_root_bh; struct affs_sb_info* s_prefix; } ;

/* Variables and functions */
 struct affs_sb_info* AFFS_SB (struct super_block*) ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  affs_brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_commit_super (struct super_block*,int) ; 
 int /*<<< orphan*/  affs_free_bitmap (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct affs_sb_info*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void
affs_put_super(struct super_block *sb)
{
	struct affs_sb_info *sbi = AFFS_SB(sb);
	pr_debug("AFFS: put_super()\n");

	lock_kernel();

	if (!(sb->s_flags & MS_RDONLY))
		affs_commit_super(sb, 1);

	kfree(sbi->s_prefix);
	affs_free_bitmap(sb);
	affs_brelse(sbi->s_root_bh);
	kfree(sbi);
	sb->s_fs_info = NULL;

	unlock_kernel();
}