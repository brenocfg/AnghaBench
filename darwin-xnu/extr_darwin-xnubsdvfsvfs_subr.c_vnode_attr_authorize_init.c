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
struct vnode_attr {int dummy; } ;
typedef  int kauth_action_t ;

/* Variables and functions */
 int EINVAL ; 
 int KAUTH_VNODE_DELETE ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_flags ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_type ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  vfs_context_issuser (int /*<<< orphan*/ ) ; 

int
vnode_attr_authorize_init(struct vnode_attr *vap, struct vnode_attr *dvap,
    kauth_action_t action, vfs_context_t ctx)
{
	VATTR_INIT(vap);
	VATTR_WANTED(vap, va_type);
	VATTR_WANTED(vap, va_mode);
	VATTR_WANTED(vap, va_flags);
	if (dvap) {
		VATTR_INIT(dvap);
		if (action & KAUTH_VNODE_DELETE) {
			VATTR_WANTED(dvap, va_type);
			VATTR_WANTED(dvap, va_mode);
			VATTR_WANTED(dvap, va_flags);
		}
	} else if (action & KAUTH_VNODE_DELETE) {
		return (EINVAL);
	}

	if (!vfs_context_issuser(ctx)) {
		VATTR_WANTED(vap, va_uid);
		VATTR_WANTED(vap, va_gid);
		VATTR_WANTED(vap, va_acl);
		if (dvap && (action & KAUTH_VNODE_DELETE)) {
			VATTR_WANTED(dvap, va_uid);
			VATTR_WANTED(dvap, va_gid);
			VATTR_WANTED(dvap, va_acl);
		}
	}

	return (0);
}