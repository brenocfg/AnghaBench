#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
struct nameidata {TYPE_1__* ni_vp; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
struct TYPE_6__ {scalar_t__ v_type; } ;

/* Variables and functions */
 int AUDITVNPATH1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  KAUTH_VNODE_READ_DATA ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NOFOLLOW ; 
 int /*<<< orphan*/  OP_READLINK ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 scalar_t__ VLNK ; 
 int VNOP_READLINK (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mac_vnode_check_readlink (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int nameiat (struct nameidata*,int) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uio_createwithbuffer (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ ) ; 
 int vnode_authorize (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 

__attribute__((used)) static int
readlinkat_internal(vfs_context_t ctx, int fd, user_addr_t path,
    enum uio_seg seg, user_addr_t buf, size_t bufsize, enum uio_seg bufseg,
    int *retval)
{
	vnode_t vp;
	uio_t auio;
	int error;
	struct nameidata nd;
	char uio_buf[ UIO_SIZEOF(1) ];

	NDINIT(&nd, LOOKUP, OP_READLINK, NOFOLLOW | AUDITVNPATH1,
	    seg, path, ctx);

	error = nameiat(&nd, fd);
	if (error)
		return (error);
	vp = nd.ni_vp;

	nameidone(&nd);

	auio = uio_createwithbuffer(1, 0, bufseg, UIO_READ,
                                    &uio_buf[0], sizeof(uio_buf));
	uio_addiov(auio, buf, bufsize);
	if (vp->v_type != VLNK) {
		error = EINVAL;
	} else {
#if CONFIG_MACF
		error = mac_vnode_check_readlink(ctx, vp);
#endif
		if (error == 0)
			error = vnode_authorize(vp, NULL, KAUTH_VNODE_READ_DATA,
			                        ctx);
		if (error == 0)
			error = VNOP_READLINK(vp, auio, ctx);
	}
	vnode_put(vp);

	*retval = bufsize - (int)uio_resid(auio);
	return (error);
}