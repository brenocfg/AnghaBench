#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct path {scalar_t__ dentry; TYPE_4__* mnt; } ;
struct file {int dummy; } ;
struct autofs_sb_info {TYPE_2__* sb; } ;
struct TYPE_11__ {unsigned int devid; unsigned int magic; } ;
struct TYPE_7__ {unsigned int type; } ;
struct TYPE_12__ {TYPE_5__ out; TYPE_1__ in; } ;
struct autofs_dev_ioctl {int size; char* path; int ioctlfd; TYPE_6__ ismountpoint; } ;
typedef  unsigned int dev_t ;
struct TYPE_10__ {scalar_t__ mnt_root; TYPE_3__* mnt_sb; } ;
struct TYPE_9__ {unsigned int s_dev; unsigned int s_magic; } ;
struct TYPE_8__ {unsigned int s_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 scalar_t__ autofs_type_any (unsigned int) ; 
 int find_autofs_mount (char const*,struct path*,int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ follow_down (struct path*) ; 
 int have_submounts (scalar_t__) ; 
 int kern_path (char const*,int /*<<< orphan*/ ,struct path*) ; 
 unsigned int new_encode_dev (unsigned int) ; 
 int /*<<< orphan*/  path_put (struct path*) ; 
 int /*<<< orphan*/  test_by_dev ; 
 int /*<<< orphan*/  test_by_type ; 

__attribute__((used)) static int autofs_dev_ioctl_ismountpoint(struct file *fp,
					 struct autofs_sb_info *sbi,
					 struct autofs_dev_ioctl *param)
{
	struct path path;
	const char *name;
	unsigned int type;
	unsigned int devid, magic;
	int err = -ENOENT;

	if (param->size <= sizeof(*param)) {
		err = -EINVAL;
		goto out;
	}

	name = param->path;
	type = param->ismountpoint.in.type;

	param->ismountpoint.out.devid = devid = 0;
	param->ismountpoint.out.magic = magic = 0;

	if (!fp || param->ioctlfd == -1) {
		if (autofs_type_any(type))
			err = kern_path(name, LOOKUP_FOLLOW, &path);
		else
			err = find_autofs_mount(name, &path, test_by_type, &type);
		if (err)
			goto out;
		devid = new_encode_dev(path.mnt->mnt_sb->s_dev);
		err = 0;
		if (path.mnt->mnt_root == path.dentry) {
			err = 1;
			magic = path.mnt->mnt_sb->s_magic;
		}
	} else {
		dev_t dev = sbi->sb->s_dev;

		err = find_autofs_mount(name, &path, test_by_dev, &dev);
		if (err)
			goto out;

		devid = new_encode_dev(dev);

		err = have_submounts(path.dentry);

		if (follow_down(&path))
			magic = path.mnt->mnt_sb->s_magic;
	}

	param->ismountpoint.out.devid = devid;
	param->ismountpoint.out.magic = magic;
	path_put(&path);
out:
	return err;
}