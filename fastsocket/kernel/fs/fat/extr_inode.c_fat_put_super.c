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
struct super_block {int /*<<< orphan*/ * s_fs_info; scalar_t__ s_dirt; } ;
struct TYPE_2__ {scalar_t__ iocharset; } ;
struct msdos_sb_info {TYPE_1__ options; int /*<<< orphan*/  nls_io; int /*<<< orphan*/  nls_disk; int /*<<< orphan*/  fat_inode; } ;

/* Variables and functions */
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 scalar_t__ fat_default_iocharset ; 
 int /*<<< orphan*/  fat_write_super (struct super_block*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct msdos_sb_info*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void fat_put_super(struct super_block *sb)
{
	struct msdos_sb_info *sbi = MSDOS_SB(sb);

	lock_kernel();

	if (sb->s_dirt)
		fat_write_super(sb);

	iput(sbi->fat_inode);

	unload_nls(sbi->nls_disk);
	unload_nls(sbi->nls_io);

	if (sbi->options.iocharset != fat_default_iocharset)
		kfree(sbi->options.iocharset);

	sb->s_fs_info = NULL;
	kfree(sbi);

	unlock_kernel();
}