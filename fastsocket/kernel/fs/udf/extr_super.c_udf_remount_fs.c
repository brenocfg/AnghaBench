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
struct udf_sb_info {scalar_t__ s_lvid_bh; int /*<<< orphan*/  s_dmode; int /*<<< orphan*/  s_fmode; int /*<<< orphan*/  s_umask; int /*<<< orphan*/  s_gid; int /*<<< orphan*/  s_uid; int /*<<< orphan*/  s_flags; } ;
struct udf_options {int /*<<< orphan*/  dmode; int /*<<< orphan*/  fmode; int /*<<< orphan*/  umask; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  flags; } ;
struct super_block {int s_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  minUDFWriteRev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOSYS ; 
 int MS_RDONLY ; 
 int UDF_MAX_WRITE_VERSION ; 
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  udf_close_lvid (struct super_block*) ; 
 int /*<<< orphan*/  udf_open_lvid (struct super_block*) ; 
 int /*<<< orphan*/  udf_parse_options (char*,struct udf_options*,int) ; 
 TYPE_1__* udf_sb_lvidiu (struct udf_sb_info*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int vfs_dq_off (struct super_block*,int) ; 
 int /*<<< orphan*/  vfs_dq_quota_on_remount (struct super_block*) ; 

__attribute__((used)) static int udf_remount_fs(struct super_block *sb, int *flags, char *options)
{
	struct udf_options uopt;
	struct udf_sb_info *sbi = UDF_SB(sb);
	int error = 0;

	uopt.flags = sbi->s_flags;
	uopt.uid   = sbi->s_uid;
	uopt.gid   = sbi->s_gid;
	uopt.umask = sbi->s_umask;
	uopt.fmode = sbi->s_fmode;
	uopt.dmode = sbi->s_dmode;

	if (!udf_parse_options(options, &uopt, true))
		return -EINVAL;

	lock_kernel();
	sbi->s_flags = uopt.flags;
	sbi->s_uid   = uopt.uid;
	sbi->s_gid   = uopt.gid;
	sbi->s_umask = uopt.umask;
	sbi->s_fmode = uopt.fmode;
	sbi->s_dmode = uopt.dmode;

	if (sbi->s_lvid_bh) {
		int write_rev = le16_to_cpu(udf_sb_lvidiu(sbi)->minUDFWriteRev);
		if (write_rev > UDF_MAX_WRITE_VERSION)
			*flags |= MS_RDONLY;
	}

	if ((*flags & MS_RDONLY) == (sb->s_flags & MS_RDONLY))
		goto out_unlock;

	if (*flags & MS_RDONLY) {
		udf_close_lvid(sb);

		error = vfs_dq_off(sb, 1);
		if (error < 0 && error != -ENOSYS)
			error = -EBUSY;
	} else {
		udf_open_lvid(sb);

		/* mark the fs r/w for quota activity */
		sb->s_flags &= ~MS_RDONLY;
		vfs_dq_quota_on_remount(sb);
	}

out_unlock:
	unlock_kernel();
	return error;
}