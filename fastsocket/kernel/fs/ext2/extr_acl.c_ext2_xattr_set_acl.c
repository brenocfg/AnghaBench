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
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  POSIX_ACL ; 
 int PTR_ERR (struct posix_acl*) ; 
 int ext2_set_acl (struct inode*,int,struct posix_acl*) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_valid (struct posix_acl*) ; 
 int /*<<< orphan*/  test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ext2_xattr_set_acl(struct inode *inode, int type, const void *value,
		   size_t size)
{
	struct posix_acl *acl;
	int error;

	if (!test_opt(inode->i_sb, POSIX_ACL))
		return -EOPNOTSUPP;
	if (!is_owner_or_cap(inode))
		return -EPERM;

	if (value) {
		acl = posix_acl_from_xattr(value, size);
		if (IS_ERR(acl))
			return PTR_ERR(acl);
		else if (acl) {
			error = posix_acl_valid(acl);
			if (error)
				goto release_and_out;
		}
	} else
		acl = NULL;

	error = ext2_set_acl(inode, type, acl);

release_and_out:
	posix_acl_release(acl);
	return error;
}