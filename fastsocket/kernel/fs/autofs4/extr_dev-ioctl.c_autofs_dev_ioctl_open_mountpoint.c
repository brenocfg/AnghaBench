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
struct path {int /*<<< orphan*/  mnt; int /*<<< orphan*/  dentry; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct file*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PTR_ERR (struct file*) ; 
 int /*<<< orphan*/  autofs_dev_ioctl_fd_install (int,struct file*) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct file* dentry_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_autofs_mount (char const*,struct path*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int get_unused_fd () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  put_unused_fd (int) ; 
 int /*<<< orphan*/  test_by_dev ; 

__attribute__((used)) static int autofs_dev_ioctl_open_mountpoint(const char *name, dev_t devid)
{
	int err, fd;

	fd = get_unused_fd();
	if (likely(fd >= 0)) {
		struct file *filp;
		struct path path;

		err = find_autofs_mount(name, &path, test_by_dev, &devid);
		if (err)
			goto out;

		/*
		 * Find autofs super block that has the device number
		 * corresponding to the autofs fs we want to open.
		 */

		filp = dentry_open(path.dentry, path.mnt, O_RDONLY,
				   current_cred());
		if (IS_ERR(filp)) {
			err = PTR_ERR(filp);
			goto out;
		}

		autofs_dev_ioctl_fd_install(fd, filp);
	}

	return fd;

out:
	put_unused_fd(fd);
	return err;
}