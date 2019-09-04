#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vauth_ctx ;
typedef  int /*<<< orphan*/  mount_t ;
typedef  int kauth_ace_rights_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  va_mode; } ;
struct TYPE_9__ {scalar_t__ va_type; int va_mode; } ;
struct TYPE_8__ {TYPE_4__* vap; TYPE_4__* dvap; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
 int KAUTH_VNODE_CHECKIMMUTABLE ; 
 int KAUTH_VNODE_DELETE ; 
 int KAUTH_VNODE_DELETE_CHILD ; 
 int KAUTH_VNODE_EXECUTE ; 
 int KAUTH_VNODE_LINKTARGET ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VATTR_IS_SUPPORTED (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ VREG ; 
 TYPE_6__ va ; 
 int /*<<< orphan*/  va_mode ; 
 int vnode_authorize_checkimmutable (int /*<<< orphan*/ ,TYPE_4__*,int,int) ; 
 int vnode_authorize_delete (TYPE_1__*,int) ; 
 int vnode_authorize_simple (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp ; 

__attribute__((used)) static int
vnode_attr_authorize_internal(vauth_ctx vcp, mount_t mp,
    kauth_ace_rights_t rights, int is_suser, boolean_t *found_deny,
    int noimmutable, int parent_authorized_for_delete_child)
{
	int result;

	/*
	 * Check for immutability.
	 *
	 * In the deletion case, parent directory immutability vetoes specific
	 * file rights.
	 */
	if ((result = vnode_authorize_checkimmutable(mp, vcp->vap, rights,
	    noimmutable)) != 0)
		goto out;

	if ((rights & KAUTH_VNODE_DELETE) &&
	    !parent_authorized_for_delete_child) {
		result = vnode_authorize_checkimmutable(mp, vcp->dvap,
		    KAUTH_VNODE_DELETE_CHILD, 0);
		if (result)
			goto out;
	}

	/*
	 * Clear rights that have been authorized by reaching this point, bail if nothing left to
	 * check.
	 */
	rights &= ~(KAUTH_VNODE_LINKTARGET | KAUTH_VNODE_CHECKIMMUTABLE);
	if (rights == 0)
		goto out;

	/*
	 * If we're not the superuser, authorize based on file properties;
	 * note that even if parent_authorized_for_delete_child is TRUE, we
	 * need to check on the node itself.
	 */
	if (!is_suser) {
		/* process delete rights */
		if ((rights & KAUTH_VNODE_DELETE) &&
		    ((result = vnode_authorize_delete(vcp, parent_authorized_for_delete_child)) != 0))
		    goto out;

		/* process remaining rights */
		if ((rights & ~KAUTH_VNODE_DELETE) &&
		    (result = vnode_authorize_simple(vcp, rights, rights & KAUTH_VNODE_DELETE, found_deny)) != 0)
			goto out;
	} else {
		/*
		 * Execute is only granted to root if one of the x bits is set.  This check only
		 * makes sense if the posix mode bits are actually supported.
		 */
		if ((rights & KAUTH_VNODE_EXECUTE) &&
		    (vcp->vap->va_type == VREG) &&
		    VATTR_IS_SUPPORTED(vcp->vap, va_mode) &&
		    !(vcp->vap->va_mode & (S_IXUSR | S_IXGRP | S_IXOTH))) {
			result = EPERM;
			KAUTH_DEBUG("%p    DENIED - root execute requires at least one x bit in 0x%x", vp, va.va_mode);
			goto out;
		}

		/* Assume that there were DENYs so we don't wrongly cache KAUTH_VNODE_SEARCHBYANYONE */
		*found_deny = TRUE;

		KAUTH_DEBUG("%p    ALLOWED - caller is superuser", vp);
	}
out:
	return (result);
}