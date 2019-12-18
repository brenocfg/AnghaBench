#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  unsigned short uid_t ;
struct vnode_attr {int dummy; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
typedef  int /*<<< orphan*/  name ;
typedef  unsigned short gid_t ;
struct TYPE_3__ {int /*<<< orphan*/ * dn_clone; } ;
typedef  TYPE_1__ devnode_t ;
struct TYPE_4__ {char* de_name; TYPE_1__* de_dnp; } ;
typedef  TYPE_2__ devdirent_t ;

/* Variables and functions */
 unsigned short ALLPERMS ; 
 int /*<<< orphan*/  CAST_USER_ADDR_T (char*) ; 
 int EACCES ; 
 int ERESTART ; 
 int /*<<< orphan*/  FOLLOW ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_SETATTR ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,unsigned short) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 
 int vnode_setattr (int /*<<< orphan*/ ,struct vnode_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_devfs_setattr(void * handle, unsigned short mode, uid_t uid, gid_t gid)
{
	devdirent_t		*direntp = (devdirent_t *)handle;
	devnode_t		*devnodep;
	int			error = EACCES;
	vfs_context_t		ctx = vfs_context_current();;
	struct vnode_attr	va;

	VATTR_INIT(&va);
	VATTR_SET(&va, va_uid, uid);
	VATTR_SET(&va, va_gid, gid);
	VATTR_SET(&va, va_mode, mode & ALLPERMS);

	/*
	 * If the TIOCPTYGRANT loses the race with the clone operation because
	 * this function is not part of devfs, and therefore can't take the
	 * devfs lock to protect the direntp update, then force user space to
	 * redrive the grant request.
	 */
	if (direntp == NULL || (devnodep = direntp->de_dnp) == NULL) {
		error = ERESTART;
		goto out;
	}

	/*
	 * Only do this if we are operating on device that doesn't clone
	 * each time it's referenced.  We perform a lookup on the device
	 * to insure we get the right instance.  We can't just use the call
	 * to devfs_dntovn() to get the vp for the operation, because
	 * dn_dvm may not have been initialized.
	 */
	if (devnodep->dn_clone == NULL) {
		struct nameidata nd;
		char name[128];

		snprintf(name, sizeof(name), "/dev/%s", direntp->de_name);
		NDINIT(&nd, LOOKUP, OP_SETATTR, FOLLOW, UIO_SYSSPACE, CAST_USER_ADDR_T(name), ctx);
		error = namei(&nd);
		if (error)
			goto out;
		error = vnode_setattr(nd.ni_vp, &va, ctx);
		vnode_put(nd.ni_vp);
		nameidone(&nd);
		goto out;
	}

out:
	return(error);
}