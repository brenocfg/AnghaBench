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
struct the_nilfs {int /*<<< orphan*/  ns_sem; } ;
struct super_block {scalar_t__ s_dirt; } ;
struct nilfs_sb_info {struct the_nilfs* s_nilfs; } ;

/* Variables and functions */
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_commit_super (struct nilfs_sb_info*,int) ; 
 int nilfs_construct_segment (struct super_block*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_sync_fs(struct super_block *sb, int wait)
{
	struct nilfs_sb_info *sbi = NILFS_SB(sb);
	struct the_nilfs *nilfs = sbi->s_nilfs;
	int err = 0;

	/* This function is called when super block should be written back */
	if (wait)
		err = nilfs_construct_segment(sb);

	down_write(&nilfs->ns_sem);
	if (sb->s_dirt)
		nilfs_commit_super(sbi, 1);
	up_write(&nilfs->ns_sem);

	return err;
}