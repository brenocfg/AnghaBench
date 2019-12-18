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
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
struct vnode {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (char*) ; 
 int EROFS ; 
 int /*<<< orphan*/  FSE_ARG_DONE ; 
 int /*<<< orphan*/  FSE_ARG_VNODE ; 
 int /*<<< orphan*/  FSE_XATTR_MODIFIED ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int XATTR_NOSECURITY ; 
 int /*<<< orphan*/  add_fsevent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 scalar_t__ vfs_isrdonly (int /*<<< orphan*/ ) ; 
 int vn_setxattr (struct vnode*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
mac_vnop_setxattr (struct vnode *vp, const char *name, char *buf, size_t len)
{
	vfs_context_t ctx;
	int options = XATTR_NOSECURITY;
	char uio_buf[ UIO_SIZEOF(1) ];
        uio_t auio;
	int error;

	if (vfs_isrdonly(vp->v_mount))
		return (EROFS);

	ctx = vfs_context_current();
	auio = uio_createwithbuffer(1, 0, UIO_SYSSPACE, UIO_WRITE,
				    &uio_buf[0], sizeof(uio_buf));
	uio_addiov(auio, CAST_USER_ADDR_T(buf), len);

	error = vn_setxattr(vp, name, auio, options, ctx);
#if CONFIG_FSE
	if (error == 0) {
		add_fsevent(FSE_XATTR_MODIFIED, ctx,
		    FSE_ARG_VNODE, vp,
		    FSE_ARG_DONE);
	}
#endif

	return (error);
}