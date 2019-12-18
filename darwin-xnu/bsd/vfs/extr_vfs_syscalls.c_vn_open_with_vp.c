#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct TYPE_11__ {int p_flag; int /*<<< orphan*/  p_acflag; } ;
struct TYPE_10__ {int v_flag; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KAUTH_FILEOP_OPEN ; 
 int KAUTH_VNODE_APPEND_DATA ; 
 int KAUTH_VNODE_READ_DATA ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int O_APPEND ; 
 int O_EVTONLY ; 
 int O_TRUNC ; 
 int P_CHECKOPENEVT ; 
 int /*<<< orphan*/  VNOP_CLOSE (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int VNOP_OPEN (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int VOPENEVT ; 
 TYPE_7__* current_proc () ; 
 int /*<<< orphan*/  kauth_authorize_fileop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int mac_vnode_check_open (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mac_vnode_notify_open (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int suser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_authorize (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int vnode_ref_ext (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vn_open_with_vp(vnode_t vp, int fmode, vfs_context_t ctx)
{
	int error, action;

	if ((error = suser(kauth_cred_get(), &(current_proc()->p_acflag)))) {
		return error;
	}

#if CONFIG_MACF
	error = mac_vnode_check_open(ctx, vp, fmode);
	if (error)
		return error;
#endif

	/* compute action to be authorized */
	action = 0;
	if (fmode & FREAD) {
		action |= KAUTH_VNODE_READ_DATA;
	}
	if (fmode & (FWRITE | O_TRUNC)) {
		/*
		 * If we are writing, appending, and not truncating,
		 * indicate that we are appending so that if the
		 * UF_APPEND or SF_APPEND bits are set, we do not deny
		 * the open.
		 */
		if ((fmode & O_APPEND) && !(fmode & O_TRUNC)) {
			action |= KAUTH_VNODE_APPEND_DATA;
		} else {
			action |= KAUTH_VNODE_WRITE_DATA;
		}
	}

	if ((error = vnode_authorize(vp, NULL, action, ctx)) != 0)
		return error;


	//
	// if the vnode is tagged VOPENEVT and the current process
	// has the P_CHECKOPENEVT flag set, then we or in the O_EVTONLY
	// flag to the open mode so that this open won't count against
	// the vnode when carbon delete() does a vnode_isinuse() to see
	// if a file is currently in use.  this allows spotlight
	// importers to not interfere with carbon apps that depend on
	// the no-delete-if-busy semantics of carbon delete().
	//
	if ((vp->v_flag & VOPENEVT) && (current_proc()->p_flag & P_CHECKOPENEVT)) {
		fmode |= O_EVTONLY;
	}

	if ( (error = VNOP_OPEN(vp, fmode, ctx)) ) {
		return error;
	}
	if ( (error = vnode_ref_ext(vp, fmode, 0)) ) {
		VNOP_CLOSE(vp, fmode, ctx);
		return error;
	}

	/* Call out to allow 3rd party notification of open.
	 * Ignore result of kauth_authorize_fileop call.
	 */
#if CONFIG_MACF
	mac_vnode_notify_open(ctx, vp, fmode);
#endif
	kauth_authorize_fileop(vfs_context_ucred(ctx), KAUTH_FILEOP_OPEN,
			       (uintptr_t)vp, 0);


	return 0;
}