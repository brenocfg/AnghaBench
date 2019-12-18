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
typedef  int /*<<< orphan*/  uint32_t ;
struct vnode_attr {int va_vaflags; scalar_t__ va_type; int /*<<< orphan*/ * va_base_acl; int /*<<< orphan*/ * va_acl; } ;
typedef  int /*<<< orphan*/ * kauth_acl_t ;
struct TYPE_6__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  KAUTH_DEBUG (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  VATTR_CLEAR_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int VA_NOAUTH ; 
 int VA_NOINHERIT ; 
 scalar_t__ VDIR ; 
 int kauth_acl_inherit (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_acl ; 
 scalar_t__ vfs_extendedsecurity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_attribute_cleanup (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int vnode_authattr_new_internal (TYPE_1__*,struct vnode_attr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
vn_attribute_prepare(vnode_t dvp, struct vnode_attr *vap, uint32_t *defaulted_fieldsp, vfs_context_t ctx)
{
	kauth_acl_t nacl = NULL, oacl = NULL;
	int error;

	/*
	 * Handle ACL inheritance.
	 */
	if (!(vap->va_vaflags & VA_NOINHERIT) && vfs_extendedsecurity(dvp->v_mount)) {
		/* save the original filesec */
		if (VATTR_IS_ACTIVE(vap, va_acl)) {
			oacl = vap->va_acl;
		}

		vap->va_acl = NULL;
		if ((error = kauth_acl_inherit(dvp,
			 oacl,
			 &nacl,
			 vap->va_type == VDIR,
			 ctx)) != 0) {
			KAUTH_DEBUG("%p    CREATE - error %d processing inheritance", dvp, error);
			return(error);
		}

		/*
		 * If the generated ACL is NULL, then we can save ourselves some effort
		 * by clearing the active bit.
		 */
		if (nacl == NULL) {
			VATTR_CLEAR_ACTIVE(vap, va_acl);
		} else {
			vap->va_base_acl = oacl;
			VATTR_SET(vap, va_acl, nacl);
		}
	}
	
	error = vnode_authattr_new_internal(dvp, vap, (vap->va_vaflags & VA_NOAUTH), defaulted_fieldsp, ctx);
	if (error) {
		vn_attribute_cleanup(vap, *defaulted_fieldsp);
	} 

	return error;
}