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
struct the_nilfs {int /*<<< orphan*/  ns_super_sem; struct nilfs_sb_info* ns_current; int /*<<< orphan*/  ns_sem; int /*<<< orphan*/  ns_mount_state; TYPE_1__** ns_sbp; } ;
struct super_block {int s_flags; int /*<<< orphan*/ * s_fs_info; } ;
struct nilfs_sb_info {int /*<<< orphan*/ * s_super; struct the_nilfs* s_nilfs; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_state; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  nilfs_commit_super (struct nilfs_sb_info*,int) ; 
 int /*<<< orphan*/  nilfs_detach_checkpoint (struct nilfs_sb_info*) ; 
 int /*<<< orphan*/  nilfs_detach_segment_constructor (struct nilfs_sb_info*) ; 
 int /*<<< orphan*/  nilfs_put_sbinfo (struct nilfs_sb_info*) ; 
 int /*<<< orphan*/  put_nilfs (struct the_nilfs*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_put_super(struct super_block *sb)
{
	struct nilfs_sb_info *sbi = NILFS_SB(sb);
	struct the_nilfs *nilfs = sbi->s_nilfs;

	lock_kernel();

	nilfs_detach_segment_constructor(sbi);

	if (!(sb->s_flags & MS_RDONLY)) {
		down_write(&nilfs->ns_sem);
		nilfs->ns_sbp[0]->s_state = cpu_to_le16(nilfs->ns_mount_state);
		nilfs_commit_super(sbi, 1);
		up_write(&nilfs->ns_sem);
	}
	down_write(&nilfs->ns_super_sem);
	if (nilfs->ns_current == sbi)
		nilfs->ns_current = NULL;
	up_write(&nilfs->ns_super_sem);

	nilfs_detach_checkpoint(sbi);
	put_nilfs(sbi->s_nilfs);
	sbi->s_super = NULL;
	sb->s_fs_info = NULL;
	nilfs_put_sbinfo(sbi);

	unlock_kernel();
}