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
struct super_block {int dummy; } ;
struct seq_file {int dummy; } ;
struct ext4_sb_info {int s_jquota_fmt; char** s_qf_names; int s_mount_opt; } ;

/* Variables and functions */
 int EXT4_MOUNT_GRPQUOTA ; 
 int EXT4_MOUNT_USRQUOTA ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 size_t GRPQUOTA ; 
#define  QFMT_VFS_OLD 130 
#define  QFMT_VFS_V0 129 
#define  QFMT_VFS_V1 128 
 size_t USRQUOTA ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static inline void ext4_show_quota_options(struct seq_file *seq,
					   struct super_block *sb)
{
#if defined(CONFIG_QUOTA)
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	if (sbi->s_jquota_fmt) {
		char *fmtname = "";

		switch (sbi->s_jquota_fmt) {
		case QFMT_VFS_OLD:
			fmtname = "vfsold";
			break;
		case QFMT_VFS_V0:
			fmtname = "vfsv0";
			break;
		case QFMT_VFS_V1:
			fmtname = "vfsv1";
			break;
		}
		seq_printf(seq, ",jqfmt=%s", fmtname);
	}

	if (sbi->s_qf_names[USRQUOTA])
		seq_printf(seq, ",usrjquota=%s", sbi->s_qf_names[USRQUOTA]);

	if (sbi->s_qf_names[GRPQUOTA])
		seq_printf(seq, ",grpjquota=%s", sbi->s_qf_names[GRPQUOTA]);

	if (sbi->s_mount_opt & EXT4_MOUNT_USRQUOTA)
		seq_puts(seq, ",usrquota");

	if (sbi->s_mount_opt & EXT4_MOUNT_GRPQUOTA)
		seq_puts(seq, ",grpquota");
#endif
}