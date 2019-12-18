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
typedef  int umode_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct super_block {int dummy; } ;
struct hpfs_sb_info {int sb_mode; int sb_lowercase; int sb_conv; int sb_eas; int sb_chk; int sb_chkdsk; int sb_err; int sb_timeshift; int /*<<< orphan*/  sb_gid; int /*<<< orphan*/  sb_uid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MS_NOATIME ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  hpfs_help () ; 
 struct hpfs_sb_info* hpfs_sb (struct super_block*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kstrdup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  mark_dirty (struct super_block*) ; 
 int parse_opts (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int*,int*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  replace_mount_options (struct super_block*,char*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 
 int /*<<< orphan*/  unmark_dirty (struct super_block*) ; 

__attribute__((used)) static int hpfs_remount_fs(struct super_block *s, int *flags, char *data)
{
	uid_t uid;
	gid_t gid;
	umode_t umask;
	int lowercase, conv, eas, chk, errs, chkdsk, timeshift;
	int o;
	struct hpfs_sb_info *sbi = hpfs_sb(s);
	char *new_opts = kstrdup(data, GFP_KERNEL);
	
	*flags |= MS_NOATIME;
	
	lock_kernel();
	lock_super(s);
	uid = sbi->sb_uid; gid = sbi->sb_gid;
	umask = 0777 & ~sbi->sb_mode;
	lowercase = sbi->sb_lowercase; conv = sbi->sb_conv;
	eas = sbi->sb_eas; chk = sbi->sb_chk; chkdsk = sbi->sb_chkdsk;
	errs = sbi->sb_err; timeshift = sbi->sb_timeshift;

	if (!(o = parse_opts(data, &uid, &gid, &umask, &lowercase, &conv,
	    &eas, &chk, &errs, &chkdsk, &timeshift))) {
		printk("HPFS: bad mount options.\n");
		goto out_err;
	}
	if (o == 2) {
		hpfs_help();
		goto out_err;
	}
	if (timeshift != sbi->sb_timeshift) {
		printk("HPFS: timeshift can't be changed using remount.\n");
		goto out_err;
	}

	unmark_dirty(s);

	sbi->sb_uid = uid; sbi->sb_gid = gid;
	sbi->sb_mode = 0777 & ~umask;
	sbi->sb_lowercase = lowercase; sbi->sb_conv = conv;
	sbi->sb_eas = eas; sbi->sb_chk = chk; sbi->sb_chkdsk = chkdsk;
	sbi->sb_err = errs; sbi->sb_timeshift = timeshift;

	if (!(*flags & MS_RDONLY)) mark_dirty(s);

	replace_mount_options(s, new_opts);

	unlock_super(s);
	unlock_kernel();
	return 0;

out_err:
	unlock_super(s);
	unlock_kernel();
	kfree(new_opts);
	return -EINVAL;
}