#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_20__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_18__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  TYPE_2__* vfs_context_t ;
typedef  struct _vnode_authorize_context* vauth_ctx ;
struct vnode_attr {int va_mode; int /*<<< orphan*/ * va_acl; } ;
struct _vnode_authorize_context {TYPE_1__* dvp; TYPE_1__* vp; struct vnode_attr* dvap; scalar_t__ flags_valid; scalar_t__ flags; struct vnode_attr* vap; TYPE_2__* ctx; } ;
typedef  int /*<<< orphan*/ * kauth_cred_t ;
typedef  int kauth_action_t ;
typedef  int kauth_ace_rights_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_28__ {int /*<<< orphan*/ * vc_ucred; } ;
struct TYPE_27__ {int /*<<< orphan*/  p_comm; } ;
struct TYPE_26__ {char* v_name; scalar_t__ v_type; TYPE_18__* v_mount; struct TYPE_26__* v_parent; } ;
struct TYPE_25__ {int mnt_flag; int mnt_kern_flag; } ;

/* Variables and functions */
 int EACCES ; 
 int EROFS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,TYPE_1__*,...) ; 
 int KAUTH_RESULT_ALLOW ; 
 int KAUTH_RESULT_DENY ; 
 int KAUTH_VNODE_ACCESS ; 
 int KAUTH_VNODE_APPEND_DATA ; 
 int KAUTH_VNODE_CHANGE_OWNER ; 
 int KAUTH_VNODE_DELETE ; 
 int KAUTH_VNODE_DELETE_CHILD ; 
 int KAUTH_VNODE_EXECUTE ; 
 int KAUTH_VNODE_NOIMMUTABLE ; 
 int KAUTH_VNODE_READ_ATTRIBUTES ; 
 int KAUTH_VNODE_READ_DATA ; 
 int KAUTH_VNODE_READ_EXTATTRIBUTES ; 
 int KAUTH_VNODE_READ_SECURITY ; 
 int KAUTH_VNODE_SEARCH ; 
 int /*<<< orphan*/  KAUTH_VNODE_SEARCHBYANYONE ; 
 int KAUTH_VNODE_WRITE_ATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int KAUTH_VNODE_WRITE_EXTATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_RIGHTS ; 
 int KAUTH_VNODE_WRITE_SECURITY ; 
 int MNTK_AUTH_OPAQUE ; 
 int MNT_NOEXEC ; 
 int MNT_RDONLY ; 
 TYPE_1__* NULLVP ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_RETURN (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VCPLX ; 
 scalar_t__ VDIR ; 
 scalar_t__ VLNK ; 
 int VNODE_DRAINO ; 
 int VNODE_NODEAD ; 
 scalar_t__ VREG ; 
 int /*<<< orphan*/  kauth_acl_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_flags ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_type ; 
 int /*<<< orphan*/  va_uid ; 
 scalar_t__ vfs_context_issuser (TYPE_2__*) ; 
 TYPE_20__* vfs_context_proc (TYPE_2__*) ; 
 scalar_t__ vget_internal (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int vnode_attr_authorize_internal (struct _vnode_authorize_context*,TYPE_18__*,int,scalar_t__,scalar_t__*,int,scalar_t__) ; 
 scalar_t__ vnode_authorize_opaque (TYPE_1__*,int*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_cache_authorized_action (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_cache_is_authorized (TYPE_1__*,TYPE_2__*,int) ; 
 int vnode_getattr (TYPE_1__*,struct vnode_attr*,TYPE_2__*) ; 
 scalar_t__ vnode_isdir (TYPE_1__*) ; 
 scalar_t__ vnode_isnamedstream (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_vtype (TYPE_1__*) ; 

__attribute__((used)) static int
vnode_authorize_callback_int(kauth_action_t action, vfs_context_t ctx,
    vnode_t vp, vnode_t dvp, int *errorp)
{
	struct _vnode_authorize_context auth_context;
	vauth_ctx		vcp;
	kauth_cred_t		cred;
	kauth_ace_rights_t	rights;
	struct vnode_attr	va, dva;
	int			result;
	int			noimmutable;
	boolean_t		parent_authorized_for_delete_child = FALSE;
	boolean_t		found_deny = FALSE;
	boolean_t		parent_ref= FALSE;
	boolean_t		is_suser = FALSE;

	vcp = &auth_context;
	vcp->ctx = ctx;
	vcp->vp = vp;
	vcp->dvp = dvp;
	/*
	 * Note that we authorize against the context, not the passed cred
	 * (the same thing anyway)
	 */
	cred = ctx->vc_ucred;

	VATTR_INIT(&va);
	vcp->vap = &va;
	VATTR_INIT(&dva);
	vcp->dvap = &dva;

	vcp->flags = vcp->flags_valid = 0;

#if DIAGNOSTIC
	if ((ctx == NULL) || (vp == NULL) || (cred == NULL))
		panic("vnode_authorize: bad arguments (context %p  vp %p  cred %p)", ctx, vp, cred);
#endif

	KAUTH_DEBUG("%p  AUTH - %s %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s on %s '%s' (0x%x:%p/%p)",
	    vp, vfs_context_proc(ctx)->p_comm,
	    (action & KAUTH_VNODE_ACCESS)		? "access" : "auth",
	    (action & KAUTH_VNODE_READ_DATA)		? vnode_isdir(vp) ? " LIST_DIRECTORY" : " READ_DATA" : "",
	    (action & KAUTH_VNODE_WRITE_DATA)		? vnode_isdir(vp) ? " ADD_FILE" : " WRITE_DATA" : "",
	    (action & KAUTH_VNODE_EXECUTE)		? vnode_isdir(vp) ? " SEARCH" : " EXECUTE" : "",
	    (action & KAUTH_VNODE_DELETE)		? " DELETE" : "",
	    (action & KAUTH_VNODE_APPEND_DATA)		? vnode_isdir(vp) ? " ADD_SUBDIRECTORY" : " APPEND_DATA" : "",
	    (action & KAUTH_VNODE_DELETE_CHILD)		? " DELETE_CHILD" : "",
	    (action & KAUTH_VNODE_READ_ATTRIBUTES)	? " READ_ATTRIBUTES" : "",
	    (action & KAUTH_VNODE_WRITE_ATTRIBUTES)	? " WRITE_ATTRIBUTES" : "",
	    (action & KAUTH_VNODE_READ_EXTATTRIBUTES)	? " READ_EXTATTRIBUTES" : "",
	    (action & KAUTH_VNODE_WRITE_EXTATTRIBUTES)	? " WRITE_EXTATTRIBUTES" : "",
	    (action & KAUTH_VNODE_READ_SECURITY)	? " READ_SECURITY" : "",
	    (action & KAUTH_VNODE_WRITE_SECURITY)	? " WRITE_SECURITY" : "",
	    (action & KAUTH_VNODE_CHANGE_OWNER)		? " CHANGE_OWNER" : "",
	    (action & KAUTH_VNODE_NOIMMUTABLE)		? " (noimmutable)" : "",
	    vnode_isdir(vp) ? "directory" : "file",
	    vp->v_name ? vp->v_name : "<NULL>", action, vp, dvp);

	/*
	 * Extract the control bits from the action, everything else is
	 * requested rights.
	 */
	noimmutable = (action & KAUTH_VNODE_NOIMMUTABLE) ? 1 : 0;
	rights = action & ~(KAUTH_VNODE_ACCESS | KAUTH_VNODE_NOIMMUTABLE);
 
	if (rights & KAUTH_VNODE_DELETE) {
#if DIAGNOSTIC
		if (dvp == NULL)
			panic("vnode_authorize: KAUTH_VNODE_DELETE test requires a directory");
#endif
		/*
		 * check to see if we've already authorized the parent
		 * directory for deletion of its children... if so, we
		 * can skip a whole bunch of work... we will still have to
		 * authorize that this specific child can be removed
		 */
		if (vnode_cache_is_authorized(dvp, ctx, KAUTH_VNODE_DELETE_CHILD) == TRUE)
		        parent_authorized_for_delete_child = TRUE;
	} else {
		vcp->dvp = NULLVP;
		vcp->dvap = NULL;
	}
	
	/*
	 * Check for read-only filesystems.
	 */
	if ((rights & KAUTH_VNODE_WRITE_RIGHTS) &&
	    (vp->v_mount->mnt_flag & MNT_RDONLY) &&
	    ((vp->v_type == VREG) || (vp->v_type == VDIR) || 
	     (vp->v_type == VLNK) || (vp->v_type == VCPLX) || 
	     (rights & KAUTH_VNODE_DELETE) || (rights & KAUTH_VNODE_DELETE_CHILD))) {
		result = EROFS;
		goto out;
	}

	/*
	 * Check for noexec filesystems.
	 */
	if ((rights & KAUTH_VNODE_EXECUTE) && (vp->v_type == VREG) && (vp->v_mount->mnt_flag & MNT_NOEXEC)) {
		result = EACCES;
		goto out;
	}

	/*
	 * Handle cases related to filesystems with non-local enforcement.
	 * This call can return 0, in which case we will fall through to perform a
	 * check based on VNOP_GETATTR data.  Otherwise it returns 1 and sets
	 * an appropriate result, at which point we can return immediately.
	 */
	if ((vp->v_mount->mnt_kern_flag & MNTK_AUTH_OPAQUE) && vnode_authorize_opaque(vp, &result, action, ctx))
		goto out;

	/*
	 * If the vnode is a namedstream (extended attribute) data vnode (eg.
	 * a resource fork), *_DATA becomes *_EXTATTRIBUTES.
	 */
	if (vnode_isnamedstream(vp)) {
		if (rights & KAUTH_VNODE_READ_DATA) {
			rights &= ~KAUTH_VNODE_READ_DATA;
			rights |= KAUTH_VNODE_READ_EXTATTRIBUTES;
		}
		if (rights & KAUTH_VNODE_WRITE_DATA) {
			rights &= ~KAUTH_VNODE_WRITE_DATA;
			rights |= KAUTH_VNODE_WRITE_EXTATTRIBUTES;
		}

		/*
		 * Point 'vp' to the namedstream's parent for ACL checking
		 */
		if ((vp->v_parent != NULL) &&
		    (vget_internal(vp->v_parent, 0, VNODE_NODEAD | VNODE_DRAINO) == 0)) {
			parent_ref = TRUE;
			vcp->vp = vp = vp->v_parent;
		}
	}

	if (vfs_context_issuser(ctx)) {
		/*
		 * if we're not asking for execute permissions or modifications,
		 * then we're done, this action is authorized.
		 */
		if (!(rights & (KAUTH_VNODE_EXECUTE | KAUTH_VNODE_WRITE_RIGHTS)))
			goto success;

		is_suser = TRUE;
	}

	/*
	 * Get vnode attributes and extended security information for the vnode
	 * and directory if required.
	 *
	 * If we're root we only want mode bits and flags for checking
	 * execute and immutability.
	 */
	VATTR_WANTED(&va, va_mode);
	VATTR_WANTED(&va, va_flags);
	if (!is_suser) {
		VATTR_WANTED(&va, va_uid);
		VATTR_WANTED(&va, va_gid);
		VATTR_WANTED(&va, va_acl);
	}
	if ((result = vnode_getattr(vp, &va, ctx)) != 0) {
		KAUTH_DEBUG("%p    ERROR - failed to get vnode attributes - %d", vp, result);
		goto out;
	}
	VATTR_WANTED(&va, va_type);
	VATTR_RETURN(&va, va_type, vnode_vtype(vp));

	if (vcp->dvp) {
		VATTR_WANTED(&dva, va_mode);
		VATTR_WANTED(&dva, va_flags);
		if (!is_suser) {
			VATTR_WANTED(&dva, va_uid);
			VATTR_WANTED(&dva, va_gid);
			VATTR_WANTED(&dva, va_acl);
		}
		if ((result = vnode_getattr(vcp->dvp, &dva, ctx)) != 0) {
			KAUTH_DEBUG("%p    ERROR - failed to get directory vnode attributes - %d", vp, result);
			goto out;
		}
		VATTR_WANTED(&dva, va_type);
		VATTR_RETURN(&dva, va_type, vnode_vtype(vcp->dvp));
	}

	result = vnode_attr_authorize_internal(vcp, vp->v_mount, rights, is_suser,
	    &found_deny, noimmutable, parent_authorized_for_delete_child);
out:
	if (VATTR_IS_SUPPORTED(&va, va_acl) && (va.va_acl != NULL))
		kauth_acl_free(va.va_acl);
	if (VATTR_IS_SUPPORTED(&dva, va_acl) && (dva.va_acl != NULL))
		kauth_acl_free(dva.va_acl);

	if (result) {
		if (parent_ref)
			vnode_put(vp);
		*errorp = result;
		KAUTH_DEBUG("%p    DENIED - auth denied", vp);
		return(KAUTH_RESULT_DENY);
	}
	if ((rights & KAUTH_VNODE_SEARCH) && found_deny == FALSE && vp->v_type == VDIR) {
	        /*
		 * if we were successfully granted the right to search this directory
		 * and there were NO ACL DENYs for search and the posix permissions also don't
		 * deny execute, we can synthesize a global right that allows anyone to 
		 * traverse this directory during a pathname lookup without having to
		 * match the credential associated with this cache of rights.
		 *
		 * Note that we can correctly cache KAUTH_VNODE_SEARCHBYANYONE
		 * only if we actually check ACLs which we don't for root. As
		 * a workaround, the lookup fast path checks for root.
		 */
	        if (!VATTR_IS_SUPPORTED(&va, va_mode) ||
		    ((va.va_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) ==
		     (S_IXUSR | S_IXGRP | S_IXOTH))) {
		        vnode_cache_authorized_action(vp, ctx, KAUTH_VNODE_SEARCHBYANYONE);
		}
	}
success:
	if (parent_ref)
		vnode_put(vp);

	/*
	 * Note that this implies that we will allow requests for no rights, as well as
	 * for rights that we do not recognise.  There should be none of these.
	 */
	KAUTH_DEBUG("%p    ALLOWED - auth granted", vp);
	return(KAUTH_RESULT_ALLOW);
}