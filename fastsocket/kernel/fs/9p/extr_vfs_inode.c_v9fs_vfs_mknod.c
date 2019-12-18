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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 char* __getname () ; 
 int /*<<< orphan*/  __putname (char*) ; 
 int /*<<< orphan*/  new_valid_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int v9fs_vfs_mkspecial (struct inode*,struct dentry*,int,char*) ; 

__attribute__((used)) static int
v9fs_vfs_mknod(struct inode *dir, struct dentry *dentry, int mode, dev_t rdev)
{
	int retval;
	char *name;

	P9_DPRINTK(P9_DEBUG_VFS,
		" %lu,%s mode: %x MAJOR: %u MINOR: %u\n", dir->i_ino,
		dentry->d_name.name, mode, MAJOR(rdev), MINOR(rdev));

	if (!new_valid_dev(rdev))
		return -EINVAL;

	name = __getname();
	if (!name)
		return -ENOMEM;
	/* build extension */
	if (S_ISBLK(mode))
		sprintf(name, "b %u %u", MAJOR(rdev), MINOR(rdev));
	else if (S_ISCHR(mode))
		sprintf(name, "c %u %u", MAJOR(rdev), MINOR(rdev));
	else if (S_ISFIFO(mode))
		*name = 0;
	else {
		__putname(name);
		return -EINVAL;
	}

	retval = v9fs_vfs_mkspecial(dir, dentry, mode, name);
	__putname(name);

	return retval;
}