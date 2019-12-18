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
struct posix_acl {scalar_t__ a_count; } ;
struct inode {scalar_t__ i_uid; int /*<<< orphan*/  i_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  ar_posix_acl; } ;
struct gfs2_sbd {TYPE_1__ sd_args; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int ACL_TYPE_ACCESS ; 
 int ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  CAP_FOWNER ; 
 int EACCES ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 scalar_t__ GFS2_ACL_MAX_ENTRIES (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  GFS2_EATYPE_SYS ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int XATTR_CREATE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_fsuid () ; 
 int /*<<< orphan*/  forget_cached_acl (struct inode*,int) ; 
 int gfs2_acl_type (char const*) ; 
 int gfs2_set_mode (struct inode*,int /*<<< orphan*/ ) ; 
 int gfs2_xattr_set (struct inode*,int /*<<< orphan*/ ,char const*,void const*,size_t,int /*<<< orphan*/ ) ; 
 int posix_acl_equiv_mode (struct posix_acl*,int /*<<< orphan*/ *) ; 
 struct posix_acl* posix_acl_from_xattr (void const*,size_t) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_valid (struct posix_acl*) ; 
 int /*<<< orphan*/  set_cached_acl (struct inode*,int,struct posix_acl*) ; 

__attribute__((used)) static int gfs2_xattr_system_set(struct inode *inode, const char *name,
				 const void *value, size_t size, int flags)
{
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct posix_acl *acl = NULL;
	int error = 0, type;

	if (!sdp->sd_args.ar_posix_acl)
		return -EOPNOTSUPP;

	type = gfs2_acl_type(name);
	if (type < 0)
		return type;
	if (flags & XATTR_CREATE)
		return -EINVAL;
	if (type == ACL_TYPE_DEFAULT && !S_ISDIR(inode->i_mode))
		return value ? -EACCES : 0;
	if ((current_fsuid() != inode->i_uid) && !capable(CAP_FOWNER))
		return -EPERM;
	if (S_ISLNK(inode->i_mode))
		return -EOPNOTSUPP;

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
	if (acl->a_count > GFS2_ACL_MAX_ENTRIES(sdp))
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

		error = gfs2_set_mode(inode, mode);
		if (error)
			goto out_release;
	}

set_acl:
	error = gfs2_xattr_set(inode, GFS2_EATYPE_SYS, name, value, size, 0);
	if (!error) {
		if (acl)
			set_cached_acl(inode, type, acl);
		else
			forget_cached_acl(inode, type);
	}
out_release:
	posix_acl_release(acl);
out:
	return error;
}