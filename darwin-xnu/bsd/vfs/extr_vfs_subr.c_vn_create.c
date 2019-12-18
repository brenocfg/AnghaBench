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
typedef  scalar_t__ vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
struct vnode_attr {int va_type; int /*<<< orphan*/  va_acl; int /*<<< orphan*/  va_vaflags; } ;
struct componentname {int /*<<< orphan*/  cn_nameptr; } ;
struct nameidata {struct componentname ni_cnd; } ;
typedef  scalar_t__ errno_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,scalar_t__,...) ; 
 scalar_t__ NULLVP ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VATTR_ALL_SUPPORTED (struct vnode_attr*) ; 
 int /*<<< orphan*/  VA_NOAUTH ; 
 int /*<<< orphan*/  VA_NOINHERIT ; 
#define  VBLK 133 
#define  VCHR 132 
#define  VDIR 131 
#define  VFIFO 130 
 int /*<<< orphan*/  VNODE_LABEL_CREATE ; 
 int /*<<< orphan*/  VNOP_CLOSE (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ VNOP_MKNOD (scalar_t__,scalar_t__*,struct componentname*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VN_CREATE_DOOPEN ; 
 int VN_CREATE_NOAUTH ; 
 int VN_CREATE_NOINHERIT ; 
 int VN_CREATE_NOLABEL ; 
#define  VREG 129 
#define  VSOCK 128 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kdebug_lookup (scalar_t__,struct componentname*) ; 
 scalar_t__ namei_compound_available (scalar_t__,struct nameidata*) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  vn_attribute_cleanup (struct vnode_attr*,int) ; 
 scalar_t__ vn_attribute_prepare (scalar_t__,struct vnode_attr*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ vn_create_reg (scalar_t__,scalar_t__*,struct nameidata*,struct vnode_attr*,int,int,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ vn_mkdir (scalar_t__,scalar_t__*,struct nameidata*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_label (int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct componentname*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_mount (scalar_t__) ; 
 int /*<<< orphan*/  vnode_put (scalar_t__) ; 
 scalar_t__ vnode_setattr_fallback (scalar_t__,struct vnode_attr*,int /*<<< orphan*/ ) ; 

errno_t
vn_create(vnode_t dvp, vnode_t *vpp, struct nameidata *ndp, struct vnode_attr *vap, uint32_t flags, int fmode, uint32_t *statusp, vfs_context_t ctx)
{
	errno_t	error, old_error;
	vnode_t vp = (vnode_t)0;
	boolean_t batched;
	struct componentname *cnp;
	uint32_t defaulted;

	cnp = &ndp->ni_cnd;
	error = 0;
	batched = namei_compound_available(dvp, ndp) ? TRUE : FALSE;

	KAUTH_DEBUG("%p    CREATE - '%s'", dvp, cnp->cn_nameptr);

	if (flags & VN_CREATE_NOINHERIT) 
		vap->va_vaflags |= VA_NOINHERIT;
	if (flags & VN_CREATE_NOAUTH) 
		vap->va_vaflags |= VA_NOAUTH;
	/*
	 * Handle ACL inheritance, initialize vap.
	 */
	error = vn_attribute_prepare(dvp, vap, &defaulted, ctx);
	if (error) {
		return error;
	}

	if (vap->va_type != VREG && (fmode != 0 || (flags & VN_CREATE_DOOPEN) || statusp)) {
		panic("Open parameters, but not a regular file.");
	}
	if ((fmode != 0) && ((flags & VN_CREATE_DOOPEN) == 0)) {
		panic("Mode for open, but not trying to open...");
	}


	/*
	 * Create the requested node.
	 */
	switch(vap->va_type) {
	case VREG:
		error = vn_create_reg(dvp, vpp, ndp, vap, flags, fmode, statusp, ctx);
		break;
	case VDIR:
		error = vn_mkdir(dvp, vpp, ndp, vap, ctx);
		break;
	case VSOCK:
	case VFIFO:
	case VBLK:
	case VCHR:
		error = VNOP_MKNOD(dvp, vpp, cnp, vap, ctx);
		break;
	default:
		panic("vnode_create: unknown vtype %d", vap->va_type);
	}
	if (error != 0) {
		KAUTH_DEBUG("%p    CREATE - error %d returned by filesystem", dvp, error);
		goto out;
	}

	vp = *vpp;
	old_error = error;

#if CONFIG_MACF
	if (!(flags & VN_CREATE_NOLABEL)) {
		error = vnode_label(vnode_mount(vp), dvp, vp, cnp, VNODE_LABEL_CREATE, ctx);
		if (error)
			goto error;
	}
#endif

	/*
	 * If some of the requested attributes weren't handled by the VNOP,
	 * use our fallback code.
	 */
	if (!VATTR_ALL_SUPPORTED(vap) && *vpp) {
		KAUTH_DEBUG("     CREATE - doing fallback with ACL %p", vap->va_acl);
		error = vnode_setattr_fallback(*vpp, vap, ctx);
	}
#if CONFIG_MACF
error:
#endif
	if ((error != 0) && (vp != (vnode_t)0)) {

		/* If we've done a compound open, close */
		if (batched && (old_error == 0) && (vap->va_type == VREG)) {
			VNOP_CLOSE(vp, fmode, ctx);
		}

		/* Need to provide notifications if a create succeeded */
		if (!batched) {
			*vpp = (vnode_t) 0;
			vnode_put(vp);
			vp = NULLVP;
		}
	}

	/*
	 * For creation VNOPs, this is the equivalent of
	 * lookup_handle_found_vnode.
	 */
	if (kdebug_enable && *vpp)
		kdebug_lookup(*vpp, cnp);

out:
	vn_attribute_cleanup(vap, defaulted);

	return(error);
}