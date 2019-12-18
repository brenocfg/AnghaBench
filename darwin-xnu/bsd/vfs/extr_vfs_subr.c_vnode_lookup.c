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
typedef  int /*<<< orphan*/ * vfs_context_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
typedef  int errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (char const*) ; 
 int /*<<< orphan*/  CN_NBMOUNTLOOK ; 
 int EINVAL ; 
 int /*<<< orphan*/  FOLLOW ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NOCROSSMOUNT ; 
 int /*<<< orphan*/  NOFOLLOW ; 
 int /*<<< orphan*/  OP_LOOKUP ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VNODE_LOOKUP_CROSSMOUNTNOWAIT ; 
 int VNODE_LOOKUP_NOCROSSMOUNT ; 
 int VNODE_LOOKUP_NOFOLLOW ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 

errno_t
vnode_lookup(const char *path, int flags, vnode_t *vpp, vfs_context_t ctx)
{
	struct nameidata nd;
	int error;
	u_int32_t ndflags = 0;

	if (ctx == NULL) {
		return EINVAL;
	}

	if (flags & VNODE_LOOKUP_NOFOLLOW)
		ndflags = NOFOLLOW;
	else
		ndflags = FOLLOW;

	if (flags & VNODE_LOOKUP_NOCROSSMOUNT)
		ndflags |= NOCROSSMOUNT;

	if (flags & VNODE_LOOKUP_CROSSMOUNTNOWAIT)
		ndflags |= CN_NBMOUNTLOOK;

	/* XXX AUDITVNPATH1 needed ? */
	NDINIT(&nd, LOOKUP, OP_LOOKUP, ndflags, UIO_SYSSPACE,
	       CAST_USER_ADDR_T(path), ctx);

	if ((error = namei(&nd)))
		return (error);
	*vpp = nd.ni_vp;
	nameidone(&nd);
	
	return (0);
}