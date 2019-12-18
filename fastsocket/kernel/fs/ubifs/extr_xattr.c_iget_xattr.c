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
struct ubifs_info {int /*<<< orphan*/  vfs_sb; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_2__ {scalar_t__ xattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  ubifs_err (char*,...) ; 
 struct inode* ubifs_iget (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ubifs_inode (struct inode*) ; 

__attribute__((used)) static struct inode *iget_xattr(struct ubifs_info *c, ino_t inum)
{
	struct inode *inode;

	inode = ubifs_iget(c->vfs_sb, inum);
	if (IS_ERR(inode)) {
		ubifs_err("dead extended attribute entry, error %d",
			  (int)PTR_ERR(inode));
		return inode;
	}
	if (ubifs_inode(inode)->xattr)
		return inode;
	ubifs_err("corrupt extended attribute entry");
	iput(inode);
	return ERR_PTR(-EINVAL);
}