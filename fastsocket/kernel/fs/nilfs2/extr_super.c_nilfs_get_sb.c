#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct the_nilfs {int /*<<< orphan*/  ns_mount_mutex; int /*<<< orphan*/  ns_super_sem; TYPE_2__* ns_current; } ;
struct super_block {int s_flags; int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_id; int /*<<< orphan*/  s_root; } ;
struct nilfs_super_data {int flags; struct super_block* bdev; scalar_t__ sbi; scalar_t__ cno; } ;
struct file_system_type {int dummy; } ;
struct TYPE_4__ {TYPE_1__* s_super; } ;
struct TYPE_3__ {int s_flags; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct super_block*) ; 
 int MS_ACTIVE ; 
 int MS_RDONLY ; 
 int MS_VERBOSE ; 
 int PTR_ERR (struct super_block*) ; 
 int /*<<< orphan*/  bdevname (struct super_block*,char*) ; 
 int /*<<< orphan*/  block_size (struct super_block*) ; 
 int /*<<< orphan*/  close_bdev_exclusive (struct super_block*,int) ; 
 int /*<<< orphan*/  deactivate_super (struct super_block*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct the_nilfs* find_or_create_nilfs (struct super_block*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nilfs_fill_super (struct super_block*,void*,int,struct the_nilfs*) ; 
 scalar_t__ nilfs_find_sbinfo (struct the_nilfs*,int,scalar_t__) ; 
 scalar_t__ nilfs_identify (char*,struct nilfs_super_data*) ; 
 int /*<<< orphan*/  nilfs_put_sbinfo (scalar_t__) ; 
 int /*<<< orphan*/  nilfs_set_bdev_super ; 
 int /*<<< orphan*/  nilfs_test_bdev_super ; 
 struct super_block* open_bdev_exclusive (char const*,int,struct file_system_type*) ; 
 int /*<<< orphan*/  put_nilfs (struct the_nilfs*) ; 
 int /*<<< orphan*/  sb_set_blocksize (struct super_block*,int /*<<< orphan*/ ) ; 
 struct super_block* sget (struct file_system_type*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nilfs_super_data*) ; 
 int /*<<< orphan*/  simple_set_mnt (struct vfsmount*,struct super_block*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nilfs_get_sb(struct file_system_type *fs_type, int flags,
	     const char *dev_name, void *data, struct vfsmount *mnt)
{
	struct nilfs_super_data sd;
	struct super_block *s;
	struct the_nilfs *nilfs;
	int err, need_to_close = 1;

	sd.bdev = open_bdev_exclusive(dev_name, flags, fs_type);
	if (IS_ERR(sd.bdev))
		return PTR_ERR(sd.bdev);

	/*
	 * To get mount instance using sget() vfs-routine, NILFS needs
	 * much more information than normal filesystems to identify mount
	 * instance.  For snapshot mounts, not only a mount type (ro-mount
	 * or rw-mount) but also a checkpoint number is required.
	 */
	sd.cno = 0;
	sd.flags = flags;
	if (nilfs_identify((char *)data, &sd)) {
		err = -EINVAL;
		goto failed;
	}

	nilfs = find_or_create_nilfs(sd.bdev);
	if (!nilfs) {
		err = -ENOMEM;
		goto failed;
	}

	mutex_lock(&nilfs->ns_mount_mutex);

	if (!sd.cno) {
		/*
		 * Check if an exclusive mount exists or not.
		 * Snapshot mounts coexist with a current mount
		 * (i.e. rw-mount or ro-mount), whereas rw-mount and
		 * ro-mount are mutually exclusive.
		 */
		down_read(&nilfs->ns_super_sem);
		if (nilfs->ns_current &&
		    ((nilfs->ns_current->s_super->s_flags ^ flags)
		     & MS_RDONLY)) {
			up_read(&nilfs->ns_super_sem);
			err = -EBUSY;
			goto failed_unlock;
		}
		up_read(&nilfs->ns_super_sem);
	}

	/*
	 * Find existing nilfs_sb_info struct
	 */
	sd.sbi = nilfs_find_sbinfo(nilfs, !(flags & MS_RDONLY), sd.cno);

	/*
	 * Get super block instance holding the nilfs_sb_info struct.
	 * A new instance is allocated if no existing mount is present or
	 * existing instance has been unmounted.
	 */
	s = sget(fs_type, nilfs_test_bdev_super, nilfs_set_bdev_super, &sd);
	if (sd.sbi)
		nilfs_put_sbinfo(sd.sbi);

	if (IS_ERR(s)) {
		err = PTR_ERR(s);
		goto failed_unlock;
	}

	if (!s->s_root) {
		char b[BDEVNAME_SIZE];

		/* New superblock instance created */
		s->s_flags = flags;
		strlcpy(s->s_id, bdevname(sd.bdev, b), sizeof(s->s_id));
		sb_set_blocksize(s, block_size(sd.bdev));

		err = nilfs_fill_super(s, data, flags & MS_VERBOSE, nilfs);
		if (err)
			goto cancel_new;

		s->s_flags |= MS_ACTIVE;
		need_to_close = 0;
	}

	mutex_unlock(&nilfs->ns_mount_mutex);
	put_nilfs(nilfs);
	if (need_to_close)
		close_bdev_exclusive(sd.bdev, flags);
	simple_set_mnt(mnt, s);
	return 0;

 failed_unlock:
	mutex_unlock(&nilfs->ns_mount_mutex);
	put_nilfs(nilfs);
 failed:
	close_bdev_exclusive(sd.bdev, flags);

	return err;

 cancel_new:
	/* Abandoning the newly allocated superblock */
	mutex_unlock(&nilfs->ns_mount_mutex);
	put_nilfs(nilfs);
	up_write(&s->s_umount);
	deactivate_super(s);
	/*
	 * deactivate_super() invokes close_bdev_exclusive().
	 * We must finish all post-cleaning before this call;
	 * put_nilfs() needs the block device.
	 */
	return err;
}