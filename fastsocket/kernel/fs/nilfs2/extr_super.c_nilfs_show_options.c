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
struct vfsmount {struct super_block* mnt_sb; } ;
struct super_block {int dummy; } ;
struct seq_file {int dummy; } ;
struct nilfs_sb_info {scalar_t__ s_snapshot_cno; } ;

/* Variables and functions */
 int /*<<< orphan*/  BARRIER ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 int /*<<< orphan*/  ERRORS_RO ; 
 struct nilfs_sb_info* NILFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SNAPSHOT ; 
 int /*<<< orphan*/  STRICT_ORDER ; 
 scalar_t__ nilfs_test_opt (struct nilfs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int nilfs_show_options(struct seq_file *seq, struct vfsmount *vfs)
{
	struct super_block *sb = vfs->mnt_sb;
	struct nilfs_sb_info *sbi = NILFS_SB(sb);

	if (!nilfs_test_opt(sbi, BARRIER))
		seq_printf(seq, ",barrier=off");
	if (nilfs_test_opt(sbi, SNAPSHOT))
		seq_printf(seq, ",cp=%llu",
			   (unsigned long long int)sbi->s_snapshot_cno);
	if (nilfs_test_opt(sbi, ERRORS_RO))
		seq_printf(seq, ",errors=remount-ro");
	if (nilfs_test_opt(sbi, ERRORS_PANIC))
		seq_printf(seq, ",errors=panic");
	if (nilfs_test_opt(sbi, STRICT_ORDER))
		seq_printf(seq, ",order=strict");

	return 0;
}