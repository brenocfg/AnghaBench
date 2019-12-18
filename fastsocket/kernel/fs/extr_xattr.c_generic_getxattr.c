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
struct xattr_handler {int /*<<< orphan*/  (* get ) (struct inode*,char const*,void*,size_t) ;} ;
struct inode {TYPE_1__* i_sb; } ;
struct dentry {struct inode* d_inode; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_xattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  stub1 (struct inode*,char const*,void*,size_t) ; 
 struct xattr_handler* xattr_resolve_name (int /*<<< orphan*/ ,char const**) ; 

ssize_t
generic_getxattr(struct dentry *dentry, const char *name, void *buffer, size_t size)
{
	struct xattr_handler *handler;
	struct inode *inode = dentry->d_inode;

	handler = xattr_resolve_name(inode->i_sb->s_xattr, &name);
	if (!handler)
		return -EOPNOTSUPP;
	return handler->get(inode, name, buffer, size);
}