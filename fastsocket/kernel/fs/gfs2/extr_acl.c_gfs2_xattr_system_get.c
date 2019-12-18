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
struct posix_acl {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ar_posix_acl; } ;
struct gfs2_sbd {TYPE_1__ sd_args; } ;

/* Variables and functions */
 int ENODATA ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_ERR (struct posix_acl*) ; 
 int PTR_ERR (struct posix_acl*) ; 
 struct posix_acl* gfs2_acl_get (int /*<<< orphan*/ ,int) ; 
 int gfs2_acl_type (char const*) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 
 int posix_acl_to_xattr (struct posix_acl*,void*,size_t) ; 

__attribute__((used)) static int gfs2_xattr_system_get(struct inode *inode, const char *name,
				 void *buffer, size_t size)
{
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct posix_acl *acl;
	int type;
	int error;

	if (!sdp->sd_args.ar_posix_acl)
		return -EOPNOTSUPP;

	type = gfs2_acl_type(name);
	if (type < 0)
		return type;

	acl = gfs2_acl_get(GFS2_I(inode), type);
	if (IS_ERR(acl))
		return PTR_ERR(acl);
	if (acl == NULL)
		return -ENODATA;

	error = posix_acl_to_xattr(acl, buffer, size);
	posix_acl_release(acl);

	return error;
}