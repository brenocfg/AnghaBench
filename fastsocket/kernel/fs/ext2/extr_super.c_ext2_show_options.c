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
struct ext2_super_block {int /*<<< orphan*/  s_errors; int /*<<< orphan*/  s_def_resgid; int /*<<< orphan*/  s_def_resuid; int /*<<< orphan*/  s_default_mount_opts; } ;
struct ext2_sb_info {int s_sb_block; int s_resuid; int s_resgid; int s_mount_opt; struct ext2_super_block* s_es; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  ERRORS_CONT ; 
 int /*<<< orphan*/  ERRORS_PANIC ; 
 int /*<<< orphan*/  ERRORS_RO ; 
 unsigned long EXT2_DEFM_ACL ; 
 unsigned long EXT2_DEFM_BSDGROUPS ; 
 unsigned long EXT2_DEFM_XATTR_USER ; 
 int EXT2_DEF_RESGID ; 
 int EXT2_DEF_RESUID ; 
 int EXT2_ERRORS_CONTINUE ; 
 int EXT2_ERRORS_PANIC ; 
 int EXT2_MOUNT_GRPQUOTA ; 
 int EXT2_MOUNT_USRQUOTA ; 
 int EXT2_MOUNT_XIP ; 
 struct ext2_sb_info* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  GRPID ; 
 int /*<<< orphan*/  MINIX_DF ; 
 int /*<<< orphan*/  NOBH ; 
 int /*<<< orphan*/  NO_UID32 ; 
 int /*<<< orphan*/  OLDALLOC ; 
 int /*<<< orphan*/  POSIX_ACL ; 
 int /*<<< orphan*/  RESERVATION ; 
 int /*<<< orphan*/  XATTR_USER ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext2_show_options(struct seq_file *seq, struct vfsmount *vfs)
{
	struct super_block *sb = vfs->mnt_sb;
	struct ext2_sb_info *sbi = EXT2_SB(sb);
	struct ext2_super_block *es = sbi->s_es;
	unsigned long def_mount_opts;

	def_mount_opts = le32_to_cpu(es->s_default_mount_opts);

	if (sbi->s_sb_block != 1)
		seq_printf(seq, ",sb=%lu", sbi->s_sb_block);
	if (test_opt(sb, MINIX_DF))
		seq_puts(seq, ",minixdf");
	if (test_opt(sb, GRPID))
		seq_puts(seq, ",grpid");
	if (!test_opt(sb, GRPID) && (def_mount_opts & EXT2_DEFM_BSDGROUPS))
		seq_puts(seq, ",nogrpid");
	if (sbi->s_resuid != EXT2_DEF_RESUID ||
	    le16_to_cpu(es->s_def_resuid) != EXT2_DEF_RESUID) {
		seq_printf(seq, ",resuid=%u", sbi->s_resuid);
	}
	if (sbi->s_resgid != EXT2_DEF_RESGID ||
	    le16_to_cpu(es->s_def_resgid) != EXT2_DEF_RESGID) {
		seq_printf(seq, ",resgid=%u", sbi->s_resgid);
	}
	if (test_opt(sb, ERRORS_RO)) {
		int def_errors = le16_to_cpu(es->s_errors);

		if (def_errors == EXT2_ERRORS_PANIC ||
		    def_errors == EXT2_ERRORS_CONTINUE) {
			seq_puts(seq, ",errors=remount-ro");
		}
	}
	if (test_opt(sb, ERRORS_CONT))
		seq_puts(seq, ",errors=continue");
	if (test_opt(sb, ERRORS_PANIC))
		seq_puts(seq, ",errors=panic");
	if (test_opt(sb, NO_UID32))
		seq_puts(seq, ",nouid32");
	if (test_opt(sb, DEBUG))
		seq_puts(seq, ",debug");
	if (test_opt(sb, OLDALLOC))
		seq_puts(seq, ",oldalloc");

#ifdef CONFIG_EXT2_FS_XATTR
	if (test_opt(sb, XATTR_USER))
		seq_puts(seq, ",user_xattr");
	if (!test_opt(sb, XATTR_USER) &&
	    (def_mount_opts & EXT2_DEFM_XATTR_USER)) {
		seq_puts(seq, ",nouser_xattr");
	}
#endif

#ifdef CONFIG_EXT2_FS_POSIX_ACL
	if (test_opt(sb, POSIX_ACL))
		seq_puts(seq, ",acl");
	if (!test_opt(sb, POSIX_ACL) && (def_mount_opts & EXT2_DEFM_ACL))
		seq_puts(seq, ",noacl");
#endif

	if (test_opt(sb, NOBH))
		seq_puts(seq, ",nobh");

#if defined(CONFIG_QUOTA)
	if (sbi->s_mount_opt & EXT2_MOUNT_USRQUOTA)
		seq_puts(seq, ",usrquota");

	if (sbi->s_mount_opt & EXT2_MOUNT_GRPQUOTA)
		seq_puts(seq, ",grpquota");
#endif

#if defined(CONFIG_EXT2_FS_XIP)
	if (sbi->s_mount_opt & EXT2_MOUNT_XIP)
		seq_puts(seq, ",xip");
#endif

	if (!test_opt(sb, RESERVATION))
		seq_puts(seq, ",noreservation");

	return 0;
}