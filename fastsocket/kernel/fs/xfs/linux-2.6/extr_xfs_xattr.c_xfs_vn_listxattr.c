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
struct xfs_attr_list_context {int resynch; char* alist; size_t bufsize; size_t firstu; scalar_t__ count; int /*<<< orphan*/  put_listent; struct attrlist_cursor_kern* cursor; int /*<<< orphan*/  dp; } ;
struct inode {int dummy; } ;
struct dentry {struct inode* d_inode; } ;
struct attrlist_cursor_kern {int /*<<< orphan*/  member_0; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  context ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_ACCESS ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_DEFAULT ; 
 int /*<<< orphan*/  XFS_I (struct inode*) ; 
 int list_one_attr (int /*<<< orphan*/ ,scalar_t__,char*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  memset (struct xfs_attr_list_context*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ posix_acl_access_exists (struct inode*) ; 
 scalar_t__ posix_acl_default_exists (struct inode*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_attr_list_int (struct xfs_attr_list_context*) ; 
 int /*<<< orphan*/  xfs_xattr_put_listent ; 
 int /*<<< orphan*/  xfs_xattr_put_listent_sizes ; 

ssize_t
xfs_vn_listxattr(struct dentry *dentry, char *data, size_t size)
{
	struct xfs_attr_list_context context;
	struct attrlist_cursor_kern cursor = { 0 };
	struct inode		*inode = dentry->d_inode;
	int			error;

	/*
	 * First read the regular on-disk attributes.
	 */
	memset(&context, 0, sizeof(context));
	context.dp = XFS_I(inode);
	context.cursor = &cursor;
	context.resynch = 1;
	context.alist = data;
	context.bufsize = size;
	context.firstu = context.bufsize;

	if (size)
		context.put_listent = xfs_xattr_put_listent;
	else
		context.put_listent = xfs_xattr_put_listent_sizes;

	xfs_attr_list_int(&context);
	if (context.count < 0)
		return -ERANGE;

	/*
	 * Then add the two synthetic ACL attributes.
	 */
	if (posix_acl_access_exists(inode)) {
		error = list_one_attr(POSIX_ACL_XATTR_ACCESS,
				strlen(POSIX_ACL_XATTR_ACCESS) + 1,
				data, size, &context.count);
		if (error)
			return error;
	}

	if (posix_acl_default_exists(inode)) {
		error = list_one_attr(POSIX_ACL_XATTR_DEFAULT,
				strlen(POSIX_ACL_XATTR_DEFAULT) + 1,
				data, size, &context.count);
		if (error)
			return error;
	}

	return context.count;
}