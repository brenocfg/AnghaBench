#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  scalar_t__ vfs_context_t ;
typedef  int uint64_t ;
struct vnode_attr {int va_active; int va_flags; int va_supported; } ;
struct TYPE_11__ {int mnt_flag; } ;
struct TYPE_10__ {int v_flag; int v_type; TYPE_6__* v_mount; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISDIR ; 
 int ENOTSUP ; 
 int EPERM ; 
 int EROFS ; 
 int /*<<< orphan*/  FSE_ARG_DONE ; 
 int /*<<< orphan*/  FSE_ARG_VNODE ; 
 int /*<<< orphan*/  FSE_CHOWN ; 
 int /*<<< orphan*/  FSE_STAT_CHANGED ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*) ; 
 int MNT_IGNORE_OWNERSHIP ; 
 int PERMISSION_BITS ; 
 int SF_SUPPORTED ; 
 int UF_SETTABLE ; 
 int /*<<< orphan*/  VATTR_ALL_SUPPORTED (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_CLEAR_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
#define  VDIR 129 
 int VISNAMEDSTREAM ; 
 int VNODE_ATTR_ALL ; 
 int VNODE_ATTR_BIT (int /*<<< orphan*/ ) ; 
 int VNODE_ATTR_RDONLY ; 
 int VNODE_ATTR_va_data_size ; 
 int VNOP_SETATTR (TYPE_1__*,struct vnode_attr*,scalar_t__) ; 
#define  VREG 128 
 int /*<<< orphan*/  add_fsevent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ need_fsevent (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_backup_time ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_flags ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_guuid ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  va_uuuid ; 
 scalar_t__ vfs_context_kernel () ; 
 int /*<<< orphan*/  vfs_extendedsecurity (int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_isrdonly (TYPE_6__*) ; 
 scalar_t__ vnode_isswap (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_mount (TYPE_1__*) ; 
 int vnode_setattr_fallback (TYPE_1__*,struct vnode_attr*,scalar_t__) ; 

int
vnode_setattr(vnode_t vp, struct vnode_attr *vap, vfs_context_t ctx)
{
	int	error;
#if CONFIG_FSE
	uint64_t active;
	int	is_perm_change = 0;
	int	is_stat_change = 0;
#endif

	/*
	 * Reject attempts to set unknown attributes.
	 */
	if (vap->va_active & ~VNODE_ATTR_ALL)
		return (EINVAL);

	/*
	 * Make sure the filesystem is mounted R/W.
	 * If not, return an error.
	 */
	if (vfs_isrdonly(vp->v_mount)) {
		error = EROFS;
		goto out;
	}

#if DEVELOPMENT || DEBUG
	/*
	 * XXX VSWAP: Check for entitlements or special flag here
	 * so we can restrict access appropriately.
	 */
#else /* DEVELOPMENT || DEBUG */

	if (vnode_isswap(vp) && (ctx != vfs_context_kernel())) {
		error = EPERM;
		goto out;
	}
#endif /* DEVELOPMENT || DEBUG */

#if NAMEDSTREAMS
	/* For streams, va_data_size is the only setable attribute. */
	if ((vp->v_flag & VISNAMEDSTREAM) && (vap->va_active != VNODE_ATTR_va_data_size)) {
		error = EPERM;
		goto out;
	}
#endif
	/* Check for truncation */
	if(VATTR_IS_ACTIVE(vap,  va_data_size)) {
		switch(vp->v_type) {
		case VREG:
			/* For regular files it's ok */
			break;
		case VDIR:
			/* Not allowed to truncate directories */
			error = EISDIR;
			goto out;
		default:
			/* For everything else we will clear the bit and let underlying FS decide on the rest */
			VATTR_CLEAR_ACTIVE(vap, va_data_size);
			if (vap->va_active)
				break;
			/* If it was the only bit set, return success, to handle cases like redirect to /dev/null */
			return (0);
		}
	}
	
	/*
	 * If ownership is being ignored on this volume, we silently discard
	 * ownership changes.
	 */
	if (vp->v_mount->mnt_flag & MNT_IGNORE_OWNERSHIP) {
		VATTR_CLEAR_ACTIVE(vap, va_uid);
		VATTR_CLEAR_ACTIVE(vap, va_gid);
	}

	/*
	 * Make sure that extended security is enabled if we're going to try
	 * to set any.
	 */
	if (!vfs_extendedsecurity(vnode_mount(vp)) &&
	    (VATTR_IS_ACTIVE(vap, va_acl) || VATTR_IS_ACTIVE(vap, va_uuuid) || VATTR_IS_ACTIVE(vap, va_guuid))) {
		KAUTH_DEBUG("SETATTR - returning ENOTSUP to request to set extended security");
		error = ENOTSUP;
		goto out;
	}

	/* Never allow the setting of any unsupported superuser flags. */
	if (VATTR_IS_ACTIVE(vap, va_flags)) {
	    vap->va_flags &= (SF_SUPPORTED | UF_SETTABLE);
	}

#if CONFIG_FSE
	/*
	 * Remember all of the active attributes that we're
	 * attempting to modify.
	 */
	active = vap->va_active & ~VNODE_ATTR_RDONLY;
#endif

	error = VNOP_SETATTR(vp, vap, ctx);

	if ((error == 0) && !VATTR_ALL_SUPPORTED(vap))
		error = vnode_setattr_fallback(vp, vap, ctx);

#if CONFIG_FSE
#define	PERMISSION_BITS	(VNODE_ATTR_BIT(va_uid) | VNODE_ATTR_BIT(va_uuuid) | \
			 VNODE_ATTR_BIT(va_gid) | VNODE_ATTR_BIT(va_guuid) | \
			 VNODE_ATTR_BIT(va_mode) | VNODE_ATTR_BIT(va_acl))

	/*
	 * Now that we've changed them, decide whether to send an
	 * FSevent.
	 */
	if ((active & PERMISSION_BITS) & vap->va_supported) {
		is_perm_change = 1;
	} else {
		/*
		 * We've already checked the permission bits, and we
		 * also want to filter out access time / backup time
		 * changes.
		 */
		active &= ~(PERMISSION_BITS |
			    VNODE_ATTR_BIT(va_access_time) |
			    VNODE_ATTR_BIT(va_backup_time));

		/* Anything left to notify about? */
		if (active & vap->va_supported)
			is_stat_change = 1;
	}

	if (error == 0) {
	    if (is_perm_change) {
		if (need_fsevent(FSE_CHOWN, vp)) {
		    add_fsevent(FSE_CHOWN, ctx, FSE_ARG_VNODE, vp, FSE_ARG_DONE);
		}
	    } else if (is_stat_change && need_fsevent(FSE_STAT_CHANGED, vp)) {
		add_fsevent(FSE_STAT_CHANGED, ctx, FSE_ARG_VNODE, vp, FSE_ARG_DONE);
	    }
	}
#undef PERMISSION_BITS
#endif

out:
	return(error);
}