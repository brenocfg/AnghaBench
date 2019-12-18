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
struct vfsmount {int dummy; } ;
struct ubi_volume_info {int /*<<< orphan*/  cdev; int /*<<< orphan*/  vol_id; int /*<<< orphan*/  ubi_num; } ;
struct ubi_volume_desc {int s_flags; struct ubi_volume_desc* s_fs_info; scalar_t__ s_root; } ;
struct super_block {int s_flags; struct super_block* s_fs_info; scalar_t__ s_root; } ;
struct file_system_type {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (struct ubi_volume_desc*) ; 
 int MS_ACTIVE ; 
 int MS_NOATIME ; 
 int MS_RDONLY ; 
 int MS_SILENT ; 
 int PTR_ERR (struct ubi_volume_desc*) ; 
 int /*<<< orphan*/  UBI_READONLY ; 
 int /*<<< orphan*/  dbg_gen (char*,...) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct ubi_volume_desc*) ; 
 struct ubi_volume_desc* open_ubi (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_test ; 
 int /*<<< orphan*/  set_anon_super ; 
 struct ubi_volume_desc* sget (struct file_system_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_set_mnt (struct vfsmount*,struct ubi_volume_desc*) ; 
 int /*<<< orphan*/  ubi_close_volume (struct ubi_volume_desc*) ; 
 int /*<<< orphan*/  ubi_get_volume_info (struct ubi_volume_desc*,struct ubi_volume_info*) ; 
 int /*<<< orphan*/  ubifs_err (char*,char const*,int) ; 
 int ubifs_fill_super (struct ubi_volume_desc*,void*,int) ; 

__attribute__((used)) static int ubifs_get_sb(struct file_system_type *fs_type, int flags,
			const char *name, void *data, struct vfsmount *mnt)
{
	struct ubi_volume_desc *ubi;
	struct ubi_volume_info vi;
	struct super_block *sb;
	int err;

	dbg_gen("name %s, flags %#x", name, flags);

	/*
	 * Get UBI device number and volume ID. Mount it read-only so far
	 * because this might be a new mount point, and UBI allows only one
	 * read-write user at a time.
	 */
	ubi = open_ubi(name, UBI_READONLY);
	if (IS_ERR(ubi)) {
		ubifs_err("cannot open \"%s\", error %d",
			  name, (int)PTR_ERR(ubi));
		return PTR_ERR(ubi);
	}
	ubi_get_volume_info(ubi, &vi);

	dbg_gen("opened ubi%d_%d", vi.ubi_num, vi.vol_id);

	sb = sget(fs_type, &sb_test, &set_anon_super, &vi.cdev);
	if (IS_ERR(sb)) {
		err = PTR_ERR(sb);
		goto out_close;
	}

	if (sb->s_root) {
		/* A new mount point for already mounted UBIFS */
		dbg_gen("this ubi volume is already mounted");
		if ((flags ^ sb->s_flags) & MS_RDONLY) {
			err = -EBUSY;
			goto out_deact;
		}
	} else {
		sb->s_flags = flags;
		/*
		 * Pass 'ubi' to 'fill_super()' in sb->s_fs_info where it is
		 * replaced by 'c'.
		 */
		sb->s_fs_info = ubi;
		err = ubifs_fill_super(sb, data, flags & MS_SILENT ? 1 : 0);
		if (err)
			goto out_deact;
		/* We do not support atime */
		sb->s_flags |= MS_ACTIVE | MS_NOATIME;
	}

	/* 'fill_super()' opens ubi again so we must close it here */
	ubi_close_volume(ubi);

	simple_set_mnt(mnt, sb);
	return 0;

out_deact:
	deactivate_locked_super(sb);
out_close:
	ubi_close_volume(ubi);
	return err;
}