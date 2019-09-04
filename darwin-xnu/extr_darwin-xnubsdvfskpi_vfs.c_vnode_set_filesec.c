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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/ * uio_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  kauth_filesec_t ;
typedef  int /*<<< orphan*/  kauth_acl_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 scalar_t__ KAUTH_ACL_COPYSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ KAUTH_ACL_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*) ; 
 int /*<<< orphan*/  KAUTH_ENDIAN_DISK ; 
 int /*<<< orphan*/  KAUTH_ENDIAN_HOST ; 
 int /*<<< orphan*/  KAUTH_FILESEC_NOACL ; 
 scalar_t__ KAUTH_FILESEC_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KAUTH_FILESEC_XATTR ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  VFS_DEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XATTR_NOSECURITY ; 
 int /*<<< orphan*/  kauth_filesec_acl_setendian (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * uio_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 int vn_setxattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vnode_set_filesec(vnode_t vp, kauth_filesec_t fsec, kauth_acl_t acl, vfs_context_t ctx)
{
	uio_t		fsec_uio;
	int		error;
	uint32_t	saved_acl_copysize;

	fsec_uio = NULL;
	
	if ((fsec_uio = uio_create(2, 0, UIO_SYSSPACE, UIO_WRITE)) == NULL) {
		KAUTH_DEBUG("    ERROR - could not allocate iov to write ACL");	
		error = ENOMEM;
		goto out;
	}
	/*
	 * Save the pre-converted ACL copysize, because it gets swapped too
	 * if we are running with the wrong endianness.
	 */
	saved_acl_copysize = KAUTH_ACL_COPYSIZE(acl);

	kauth_filesec_acl_setendian(KAUTH_ENDIAN_DISK, fsec, acl);

	uio_addiov(fsec_uio, CAST_USER_ADDR_T(fsec), KAUTH_FILESEC_SIZE(0) - KAUTH_ACL_SIZE(KAUTH_FILESEC_NOACL));
	uio_addiov(fsec_uio, CAST_USER_ADDR_T(acl), saved_acl_copysize);
	error = vn_setxattr(vp,
	    KAUTH_FILESEC_XATTR,
	    fsec_uio,
	    XATTR_NOSECURITY, 		/* we have auth'ed already */
	    ctx);
	VFS_DEBUG(ctx, vp, "SETATTR - set ACL returning %d", error);

	kauth_filesec_acl_setendian(KAUTH_ENDIAN_HOST, fsec, acl);

out:
	if (fsec_uio != NULL)
		uio_free(fsec_uio);
	return(error);
}