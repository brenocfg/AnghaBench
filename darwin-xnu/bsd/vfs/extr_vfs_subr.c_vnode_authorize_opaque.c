#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int kauth_action_t ;
struct TYPE_7__ {int v_type; int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int ENOTSUP ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,TYPE_1__*) ; 
 int KAUTH_VNODE_ACCESS ; 
 int KAUTH_VNODE_EXECUTE ; 
#define  VBLK 131 
#define  VCHR 130 
#define  VFIFO 129 
 int VNOP_ACCESS (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VNOP_CLOSE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VNOP_OPEN (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VREG ; 
#define  VSOCK 128 
 int /*<<< orphan*/  vfs_authopaqueaccess (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vnode_authorize_opaque(vnode_t vp, int *resultp, kauth_action_t action, vfs_context_t ctx)
{
	int	error;

	/*
	 * If the vp is a device node, socket or FIFO it actually represents a local
	 * endpoint, so we need to handle it locally.
	 */
	switch(vp->v_type) {
	case VBLK:
	case VCHR:
	case VSOCK:
	case VFIFO:
		return(0);
	default:
		break;
	}

	/*
	 * In the advisory request case, if the filesystem doesn't think it's reliable
	 * we will attempt to formulate a result ourselves based on VNOP_GETATTR data.
	 */
	if ((action & KAUTH_VNODE_ACCESS) && !vfs_authopaqueaccess(vp->v_mount))
		return(0);

	/*
	 * Let the filesystem have a say in the matter.  It's OK for it to not implemnent
	 * VNOP_ACCESS, as most will authorise inline with the actual request.
	 */
	if ((error = VNOP_ACCESS(vp, action, ctx)) != ENOTSUP) {
		*resultp = error;
		KAUTH_DEBUG("%p    DENIED - opaque filesystem VNOP_ACCESS denied access", vp);
		return(1);
	}
	
	/*
	 * Typically opaque filesystems do authorisation in-line, but exec is a special case.  In
	 * order to be reasonably sure that exec will be permitted, we try a bit harder here.
	 */
	if ((action & KAUTH_VNODE_EXECUTE) && (vp->v_type == VREG)) {
		/* try a VNOP_OPEN for readonly access */
		if ((error = VNOP_OPEN(vp, FREAD, ctx)) != 0) {
			*resultp = error;
			KAUTH_DEBUG("%p    DENIED - EXECUTE denied because file could not be opened readonly", vp);
			return(1);
		}
		VNOP_CLOSE(vp, FREAD, ctx);
	}

	/*
	 * We don't have any reason to believe that the request has to be denied at this point,
	 * so go ahead and allow it.
	 */
	*resultp = 0;
	KAUTH_DEBUG("%p    ALLOWED - bypassing access check for non-local filesystem", vp);
	return(1);
}