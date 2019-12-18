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
struct posix_acl {scalar_t__ a_count; } ;
struct inode {scalar_t__ i_uid; int /*<<< orphan*/  i_mode; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  CAP_FOWNER ; 
 int EACCES ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int XATTR_CREATE ; 
 scalar_t__ XFS_ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_fsuid () ; 
 int posix_acl_equiv_mode (struct posix_acl*,int /*<<< orphan*/ *) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_valid (struct posix_acl*) ; 
 int xfs_decode_acl (char const*) ; 
 int xfs_set_acl (struct inode*,int,struct posix_acl*) ; 
 int xfs_set_mode (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_xattr_system_set(struct inode *inode, const char *name,
		const void *value, size_t size, int flags)
{
	struct posix_acl *acl = NULL;
	int error = 0, type;

	type = xfs_decode_acl(name);
	if (type < 0)
		return type;
	if (flags & XATTR_CREATE)
		return -EINVAL;
	if (type == ACL_TYPE_DEFAULT && !S_ISDIR(inode->i_mode))
		return value ? -EACCES : 0;
	if ((current_fsuid() != inode->i_uid) && !capable(CAP_FOWNER))
		return -EPERM;

	if (!value)
		goto set_acl;

	acl = posix_acl_from_xattr(value, size);
	if (!acl) {
		/*
		 * acl_set_file(3) may request that we set default ACLs with
		 * zero length -- defend (gracefully) against that here.
		 */
		goto out;
	}
	if (IS_ERR(acl)) {
		error = PTR_ERR(acl);
		goto out;
	}

	error = posix_acl_valid(acl);
	if (error)
		goto out_release;

	error = -EINVAL;
	if (acl->a_count > XFS_ACL_MAX_ENTRIES)
		goto out_release;

	if (type == ACL_TYPE_ACCESS) {
		mode_t mode = inode->i_mode;
		error = posix_acl_equiv_mode(acl, &mode);

		if (error <= 0) {
			posix_acl_release(acl);
			acl = NULL;

			if (error < 0)
				return error;
		}

		error = xfs_set_mode(inode, mode);
		if (error)
			goto out_release;
	}

 set_acl:
	error = xfs_set_acl(inode, type, acl);
 out_release:
	posix_acl_release(acl);
 out:
	return error;
}