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
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct nameidata {TYPE_2__ path; } ;
struct inode {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTBLK ; 
 int /*<<< orphan*/  LOOKUP_FOLLOW ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int path_lookup (char const*,int /*<<< orphan*/ ,struct nameidata*) ; 
 int /*<<< orphan*/  path_put (TYPE_2__*) ; 

__attribute__((used)) static int dst_lookup_device(const char *path, dev_t *dev)
{
	int err;
	struct nameidata nd;
	struct inode *inode;

	err = path_lookup(path, LOOKUP_FOLLOW, &nd);
	if (err)
		return err;

	inode = nd.path.dentry->d_inode;
	if (!inode) {
		err = -ENOENT;
		goto out;
	}

	if (!S_ISBLK(inode->i_mode)) {
		err = -ENOTBLK;
		goto out;
	}

	*dev = inode->i_rdev;

out:
	path_put(&nd.path);
	return err;
}