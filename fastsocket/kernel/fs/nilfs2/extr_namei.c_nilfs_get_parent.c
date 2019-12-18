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
struct inode {int dummy; } ;
struct TYPE_3__ {char* name; int len; } ;
struct dentry {TYPE_2__* d_inode; TYPE_1__ d_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 struct inode* nilfs_iget (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long nilfs_inode_by_name (TYPE_2__*,struct dentry*) ; 

struct dentry *nilfs_get_parent(struct dentry *child)
{
	unsigned long ino;
	struct inode *inode;
	struct dentry dotdot;

	dotdot.d_name.name = "..";
	dotdot.d_name.len = 2;

	ino = nilfs_inode_by_name(child->d_inode, &dotdot);
	if (!ino)
		return ERR_PTR(-ENOENT);

	inode = nilfs_iget(child->d_inode->i_sb, ino);
	if (IS_ERR(inode))
		return ERR_CAST(inode);
	return d_obtain_alias(inode);
}