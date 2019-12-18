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
typedef  int errno_t ;
struct TYPE_7__ {int v_lflag; scalar_t__ v_type; scalar_t__ v_data; scalar_t__ v_owner; int v_iocount; unsigned int v_id; scalar_t__ v_references; int v_flag; int /*<<< orphan*/  v_lock; scalar_t__ v_mount; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int PCATCH ; 
 int PVFS ; 
 scalar_t__ UNAGE_DIRTYTHRESHHOLD ; 
 scalar_t__ UNAGE_THRESHHOLD ; 
 scalar_t__ VBAD ; 
 int VISDIRTY ; 
 int VL_DEAD ; 
 int VL_DRAIN ; 
 int VL_SUSPENDED ; 
 int VL_TERMINATE ; 
 int VL_TERMWANT ; 
 int VNODE_ALWAYS ; 
 int VNODE_DRAINO ; 
 int VNODE_NODEAD ; 
 int VNODE_NOSUSPEND ; 
 int VNODE_WITHID ; 
 scalar_t__ current_thread () ; 
 int msleep (int*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_vp (TYPE_1__*,int) ; 
 scalar_t__ vfs_isunmount (scalar_t__) ; 
 scalar_t__ vnode_istty (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_list_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_lock_convert (TYPE_1__*) ; 

errno_t
vnode_getiocount(vnode_t vp, unsigned int vid, int vflags)
{
	int nodead = vflags & VNODE_NODEAD;
	int nosusp = vflags & VNODE_NOSUSPEND;
	int always = vflags & VNODE_ALWAYS;
	int beatdrain = vflags & VNODE_DRAINO;
	int withvid = vflags & VNODE_WITHID;

	for (;;) {
		int sleepflg = 0;

		/*
		 * if it is a dead vnode with deadfs
		 */
	        if (nodead && (vp->v_lflag & VL_DEAD) && ((vp->v_type == VBAD) || (vp->v_data == 0))) {
			return(ENOENT);
		}
		/*
		 * will return VL_DEAD ones
		 */
		if ((vp->v_lflag & (VL_SUSPENDED | VL_DRAIN | VL_TERMINATE)) == 0 ) {
			break;
		}
		/*
		 * if suspended vnodes are to be failed
		 */
		if (nosusp && (vp->v_lflag & VL_SUSPENDED)) {
			return(ENOENT);
		}
		/*
		 * if you are the owner of drain/suspend/termination , can acquire iocount
		 * check for VL_TERMINATE; it does not set owner
		 */
		if ((vp->v_lflag & (VL_DRAIN | VL_SUSPENDED | VL_TERMINATE)) &&
		    (vp->v_owner == current_thread())) {
		        break;
		}
		
		if (always != 0) 
			break;

		/*
		 * If this vnode is getting drained, there are some cases where
		 * we can't block or, in case of tty vnodes, want to be
		 * interruptible.
		 */
		if (vp->v_lflag & VL_DRAIN) {
			/*
			 * In some situations, we want to get an iocount
			 * even if the vnode is draining to prevent deadlock,
			 * e.g. if we're in the filesystem, potentially holding
			 * resources that could prevent other iocounts from
			 * being released.
			 */
			if (beatdrain)
				break;
			/*
			 * Don't block if the vnode's mount point is unmounting as
			 * we may be the thread the unmount is itself waiting on
			 * Only callers who pass in vids (at this point, we've already
			 * handled nosusp and nodead) are expecting error returns
			 * from this function, so only we can only return errors for
			 * those. ENODEV is intended to inform callers that the call
			 * failed because an unmount is in progress.
			 */
			if (withvid && (vp->v_mount) && vfs_isunmount(vp->v_mount))
				return (ENODEV);

			if (vnode_istty(vp)) {
				sleepflg = PCATCH;
			}
		}

		vnode_lock_convert(vp);

		if (vp->v_lflag & VL_TERMINATE) {
			int error;

			vp->v_lflag |= VL_TERMWANT;

			error = msleep(&vp->v_lflag,   &vp->v_lock,
			   (PVFS | sleepflg), "vnode getiocount", NULL);
			if (error)
				return (error);
		} else
			msleep(&vp->v_iocount, &vp->v_lock, PVFS, "vnode_getiocount", NULL);
	}
	if (withvid && vid != vp->v_id) {
		return(ENOENT);
	}
	if (++vp->v_references >= UNAGE_THRESHHOLD ||
	    (vp->v_flag & VISDIRTY && vp->v_references >= UNAGE_DIRTYTHRESHHOLD)) {
	        vp->v_references = 0;
		vnode_list_remove(vp);
	}
	vp->v_iocount++;
#ifdef JOE_DEBUG
	record_vp(vp, 1);
#endif
	return(0);	
}