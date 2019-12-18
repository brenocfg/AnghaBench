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
struct vnode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (char*) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int XATTR_NOSECURITY ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 size_t uio_resid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int vn_getxattr (struct vnode*,char const*,int /*<<< orphan*/ ,size_t*,int,int /*<<< orphan*/ ) ; 

int
mac_vnop_getxattr (struct vnode *vp, const char *name, char *buf, size_t len,
		   size_t *attrlen)
{
	vfs_context_t ctx = vfs_context_current();
	int options = XATTR_NOSECURITY;
	char uio_buf[ UIO_SIZEOF(1) ];
        uio_t auio;
	int error;

	auio = uio_createwithbuffer(1, 0, UIO_SYSSPACE, UIO_READ,
				    &uio_buf[0], sizeof(uio_buf));
	uio_addiov(auio, CAST_USER_ADDR_T(buf), len);

	error = vn_getxattr(vp, name, auio, attrlen, options, ctx);
	*attrlen = len - uio_resid(auio);

	return (error);
}