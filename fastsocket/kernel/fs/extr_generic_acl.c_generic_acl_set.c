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
struct posix_acl {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct generic_acl_operations {int /*<<< orphan*/  (* setacl ) (struct inode*,int,struct posix_acl*) ;} ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
#define  ACL_TYPE_ACCESS 129 
#define  ACL_TYPE_DEFAULT 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 int posix_acl_equiv_mode (struct posix_acl*,int /*<<< orphan*/ *) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_valid (struct posix_acl*) ; 
 int /*<<< orphan*/  stub1 (struct inode*,int,struct posix_acl*) ; 

int
generic_acl_set(struct inode *inode, struct generic_acl_operations *ops,
		int type, const void *value, size_t size)
{
	struct posix_acl *acl = NULL;
	int error;

	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;
	if (!is_owner_or_cap(inode))
		return -EPERM;
	if (value) {
		acl = posix_acl_from_xattr(value, size);
		if (IS_ERR(acl))
			return PTR_ERR(acl);
	}
	if (acl) {
		mode_t mode;

		error = posix_acl_valid(acl);
		if (error)
			goto failed;
		switch(type) {
			case ACL_TYPE_ACCESS:
				mode = inode->i_mode;
				error = posix_acl_equiv_mode(acl, &mode);
				if (error < 0)
					goto failed;
				inode->i_mode = mode;
				if (error == 0) {
					posix_acl_release(acl);
					acl = NULL;
				}
				break;

			case ACL_TYPE_DEFAULT:
				if (!S_ISDIR(inode->i_mode)) {
					error = -EINVAL;
					goto failed;
				}
				break;
		}
	}
	ops->setacl(inode, type, acl);
	error = 0;
failed:
	posix_acl_release(acl);
	return error;
}