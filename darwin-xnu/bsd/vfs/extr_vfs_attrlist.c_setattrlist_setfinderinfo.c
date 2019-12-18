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
typedef  int /*<<< orphan*/ * uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
struct vfs_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSE_ARG_DONE ; 
 int /*<<< orphan*/  FSE_ARG_VNODE ; 
 int /*<<< orphan*/  FSE_FINDER_INFO_CHANGED ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int /*<<< orphan*/  XATTR_FINDERINFO_NAME ; 
 int /*<<< orphan*/  XATTR_NOSECURITY ; 
 int /*<<< orphan*/  add_fsevent (int /*<<< orphan*/ ,struct vfs_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ need_fsevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 int vn_setxattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vfs_context*) ; 

__attribute__((used)) static int
setattrlist_setfinderinfo(vnode_t vp, char *fndrinfo, struct vfs_context *ctx)
{
	uio_t	auio;
	char	uio_buf[UIO_SIZEOF(1)];
	int	error;

	if ((auio = uio_createwithbuffer(1, 0, UIO_SYSSPACE, UIO_WRITE, uio_buf, sizeof(uio_buf))) == NULL) {
		error = ENOMEM;
	} else {
		uio_addiov(auio, CAST_USER_ADDR_T(fndrinfo), 32);
		error = vn_setxattr(vp, XATTR_FINDERINFO_NAME, auio, XATTR_NOSECURITY, ctx);
		uio_free(auio);
	}

#if CONFIG_FSE
	if (error == 0 && need_fsevent(FSE_FINDER_INFO_CHANGED, vp)) {
	    add_fsevent(FSE_FINDER_INFO_CHANGED, ctx, FSE_ARG_VNODE, vp, FSE_ARG_DONE);
	}
#endif
	return (error);
}