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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct hpfs_sb_info {struct hpfs_sb_info* sb_bmp_dir; struct hpfs_sb_info* sb_cp_table; } ;

/* Variables and functions */
 struct hpfs_sb_info* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct hpfs_sb_info*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  unmark_dirty (struct super_block*) ; 

__attribute__((used)) static void hpfs_put_super(struct super_block *s)
{
	struct hpfs_sb_info *sbi = hpfs_sb(s);

	lock_kernel();

	kfree(sbi->sb_cp_table);
	kfree(sbi->sb_bmp_dir);
	unmark_dirty(s);
	s->s_fs_info = NULL;
	kfree(sbi);

	unlock_kernel();
}