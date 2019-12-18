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
struct xattr_handler {int (* set ) (struct inode*,char const*,void const*,size_t,int) ;} ;
struct inode {TYPE_1__* i_sb; } ;
struct dentry {struct inode* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_xattr; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct inode*,char const*,void const*,size_t,int) ; 
 struct xattr_handler* xattr_resolve_name (int /*<<< orphan*/ ,char const**) ; 

int
generic_setxattr(struct dentry *dentry, const char *name, const void *value, size_t size, int flags)
{
	struct xattr_handler *handler;
	struct inode *inode = dentry->d_inode;

	if (size == 0)
		value = "";  /* empty EA, do not remove */
	handler = xattr_resolve_name(inode->i_sb->s_xattr, &name);
	if (!handler)
		return -EOPNOTSUPP;
	return handler->set(inode, name, value, size, flags);
}