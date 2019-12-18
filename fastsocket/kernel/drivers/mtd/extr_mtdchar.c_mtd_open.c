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
struct mtd_info {scalar_t__ type; int flags; scalar_t__ backing_dev_info; } ;
struct mtd_file_info {struct mtd_info* mtd; } ;
struct inode {int dummy; } ;
struct file {int f_mode; struct mtd_file_info* private_data; TYPE_1__* f_mapping; } ;
struct TYPE_2__ {scalar_t__ backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*) ; 
 int EACCES ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct mtd_info*) ; 
 int MAX_MTD_DEVICES ; 
 scalar_t__ MTD_ABSENT ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL0 ; 
 int MTD_WRITEABLE ; 
 int PTR_ERR (struct mtd_info*) ; 
 struct mtd_info* get_mtd_device (int /*<<< orphan*/ *,int) ; 
 int iminor (struct inode*) ; 
 struct mtd_file_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  put_mtd_device (struct mtd_info*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int mtd_open(struct inode *inode, struct file *file)
{
	int minor = iminor(inode);
	int devnum = minor >> 1;
	int ret = 0;
	struct mtd_info *mtd;
	struct mtd_file_info *mfi;

	DEBUG(MTD_DEBUG_LEVEL0, "MTD_open\n");

	if (devnum >= MAX_MTD_DEVICES)
		return -ENODEV;

	/* You can't open the RO devices RW */
	if ((file->f_mode & FMODE_WRITE) && (minor & 1))
		return -EACCES;

	lock_kernel();
	mtd = get_mtd_device(NULL, devnum);

	if (IS_ERR(mtd)) {
		ret = PTR_ERR(mtd);
		goto out;
	}

	if (mtd->type == MTD_ABSENT) {
		put_mtd_device(mtd);
		ret = -ENODEV;
		goto out;
	}

	if (mtd->backing_dev_info)
		file->f_mapping->backing_dev_info = mtd->backing_dev_info;

	/* You can't open it RW if it's not a writeable device */
	if ((file->f_mode & FMODE_WRITE) && !(mtd->flags & MTD_WRITEABLE)) {
		put_mtd_device(mtd);
		ret = -EACCES;
		goto out;
	}

	mfi = kzalloc(sizeof(*mfi), GFP_KERNEL);
	if (!mfi) {
		put_mtd_device(mtd);
		ret = -ENOMEM;
		goto out;
	}
	mfi->mtd = mtd;
	file->private_data = mfi;

out:
	unlock_kernel();
	return ret;
}