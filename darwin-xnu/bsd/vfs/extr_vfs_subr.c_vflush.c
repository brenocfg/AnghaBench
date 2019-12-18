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
struct vnode {unsigned int v_id; int v_flag; scalar_t__ v_writecount; scalar_t__ v_type; scalar_t__ v_usecount; scalar_t__ v_kusecount; int /*<<< orphan*/  v_op; int /*<<< orphan*/  v_lflag; int /*<<< orphan*/  v_iocount; int /*<<< orphan*/  v_lock; struct mount* v_mount; } ;
struct mount {int mnt_kern_flag; int /*<<< orphan*/  mnt_vnodelist; int /*<<< orphan*/  mnt_workerqueue; } ;

/* Variables and functions */
 int EBUSY ; 
 int FORCECLOSE ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MNTK_UNMOUNT_PREFLIGHT ; 
 int /*<<< orphan*/  PVFS ; 
 int SKIPROOT ; 
 int SKIPSWAP ; 
 int SKIPSYSTEM ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct vnode* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 int VDEVFLUSH ; 
 int /*<<< orphan*/  VL_DEAD ; 
 int /*<<< orphan*/  VL_TERMINATE ; 
 int /*<<< orphan*/  VL_TERMWANT ; 
 int VNOFLUSH ; 
 scalar_t__ VREG ; 
 int VROOT ; 
 int VSWAP ; 
 int VSYSTEM ; 
 int WRITECLOSE ; 
 scalar_t__ busyprt ; 
 int /*<<< orphan*/  mount_iterate_lock (struct mount*) ; 
 int /*<<< orphan*/  mount_iterate_unlock (struct mount*) ; 
 int /*<<< orphan*/  mount_lock (struct mount*) ; 
 int /*<<< orphan*/  mount_unlock (struct mount*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  record_vp (struct vnode*,int) ; 
 int /*<<< orphan*/  spec_vnodeop_p ; 
 int /*<<< orphan*/  v_mntvnodes ; 
 int /*<<< orphan*/  vclean (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_abort_advlocks (struct vnode*) ; 
 int /*<<< orphan*/  vnode_dropiocount (struct vnode*) ; 
 int /*<<< orphan*/  vnode_iterate_clear (struct mount*) ; 
 int vnode_iterate_prepare (struct mount*) ; 
 scalar_t__ vnode_iterate_reloadq (struct mount*) ; 
 int /*<<< orphan*/  vnode_iterate_setup (struct mount*) ; 
 int /*<<< orphan*/  vnode_list_add (struct vnode*) ; 
 int /*<<< orphan*/  vnode_lock_convert (struct vnode*) ; 
 int /*<<< orphan*/  vnode_lock_spin (struct vnode*) ; 
 int /*<<< orphan*/  vnode_reclaim_internal (struct vnode*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_umount_preflight (struct mount*,struct vnode*,int) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 
 int /*<<< orphan*/  vprint (char*,struct vnode*) ; 

int
vflush(struct mount *mp, struct vnode *skipvp, int flags)
{
	struct vnode *vp;
	int busy = 0;
	int reclaimed = 0;
	int retval;
	unsigned int vid;

	/*
	 * See comments in vnode_iterate() for the rationale for this lock
	 */
	mount_iterate_lock(mp);

	mount_lock(mp);
	vnode_iterate_setup(mp);
	/*
	 * On regular unmounts(not forced) do a
	 * quick check for vnodes to be in use. This
	 * preserves the caching of vnodes. automounter
	 * tries unmounting every so often to see whether
	 * it is still busy or not.
	 */
	if (((flags & FORCECLOSE)==0)  && ((mp->mnt_kern_flag & MNTK_UNMOUNT_PREFLIGHT) != 0)) {
		if (vnode_umount_preflight(mp, skipvp, flags)) {
			vnode_iterate_clear(mp);
			mount_unlock(mp);
			mount_iterate_unlock(mp);
			return(EBUSY);
		}
	}
loop:
	/* If it returns 0 then there is nothing to do */
	retval = vnode_iterate_prepare(mp);

	if (retval == 0)  {
		vnode_iterate_clear(mp);
		mount_unlock(mp);
		mount_iterate_unlock(mp);
		return(retval);
	}

	/* iterate over all the vnodes */
	while (!TAILQ_EMPTY(&mp->mnt_workerqueue)) {

		vp = TAILQ_FIRST(&mp->mnt_workerqueue);
		TAILQ_REMOVE(&mp->mnt_workerqueue, vp, v_mntvnodes);
		TAILQ_INSERT_TAIL(&mp->mnt_vnodelist, vp, v_mntvnodes);

		if ( (vp->v_mount != mp) || (vp == skipvp)) {
			continue;
		}
		vid = vp->v_id;
		mount_unlock(mp);

		vnode_lock_spin(vp);

		// If vnode is already terminating, wait for it...
		while (vp->v_id == vid && ISSET(vp->v_lflag, VL_TERMINATE)) {
			vp->v_lflag |= VL_TERMWANT;
			msleep(&vp->v_lflag, &vp->v_lock, PVFS, "vflush", NULL);
		}

		if ((vp->v_id != vid) || ISSET(vp->v_lflag, VL_DEAD)) {
				vnode_unlock(vp);
				mount_lock(mp);
				continue;
		}

		/*
		 * If requested, skip over vnodes marked VSYSTEM.
		 * Skip over all vnodes marked VNOFLUSH.
                 */
		if ((flags & SKIPSYSTEM) && ((vp->v_flag & VSYSTEM) ||
		    (vp->v_flag & VNOFLUSH))) {
			vnode_unlock(vp);
			mount_lock(mp);
			continue;
		}
		/*
		 * If requested, skip over vnodes marked VSWAP.
		 */
		if ((flags & SKIPSWAP) && (vp->v_flag & VSWAP)) {
			vnode_unlock(vp);
			mount_lock(mp);
			continue;
		}
		/*
		 * If requested, skip over vnodes marked VROOT.
		 */
		if ((flags & SKIPROOT) && (vp->v_flag & VROOT)) {
			vnode_unlock(vp);
			mount_lock(mp);
			continue;
		}
		/*
		 * If WRITECLOSE is set, only flush out regular file
		 * vnodes open for writing.
		 */
		if ((flags & WRITECLOSE) &&
		    (vp->v_writecount == 0 || vp->v_type != VREG)) {
			vnode_unlock(vp);
			mount_lock(mp);
			continue;
		}
		/*
		 * If the real usecount is 0, all we need to do is clear
		 * out the vnode data structures and we are done.
		 */
		if (((vp->v_usecount == 0) ||
		    ((vp->v_usecount - vp->v_kusecount) == 0))) {

			vnode_lock_convert(vp);
		        vp->v_iocount++;	/* so that drain waits for * other iocounts */
#ifdef JOE_DEBUG
			record_vp(vp, 1);
#endif
			vnode_reclaim_internal(vp, 1, 1, 0);
			vnode_dropiocount(vp);
			vnode_list_add(vp);
			vnode_unlock(vp);

			reclaimed++;
			mount_lock(mp);
			continue;
		}
		/*
		 * If FORCECLOSE is set, forcibly close the vnode.
		 * For block or character devices, revert to an
		 * anonymous device. For all other files, just kill them.
		 */
		if (flags & FORCECLOSE) {
			vnode_lock_convert(vp);

			if (vp->v_type != VBLK && vp->v_type != VCHR) {
				vp->v_iocount++;	/* so that drain waits * for other iocounts */
#ifdef JOE_DEBUG
				record_vp(vp, 1);
#endif
				vnode_abort_advlocks(vp);
				vnode_reclaim_internal(vp, 1, 1, 0);
				vnode_dropiocount(vp);
				vnode_list_add(vp);
				vnode_unlock(vp);
			} else {
				vclean(vp, 0);
				vp->v_lflag &= ~VL_DEAD;
				vp->v_op = spec_vnodeop_p;
				vp->v_flag |= VDEVFLUSH;
				vnode_unlock(vp);
			}
			mount_lock(mp);
			continue;
		}
#if DIAGNOSTIC
		if (busyprt)
			vprint("vflush: busy vnode", vp);
#endif
		vnode_unlock(vp);
		mount_lock(mp);
		busy++;
	}

	/* At this point the worker queue is completed */
	if (busy && ((flags & FORCECLOSE)==0) && reclaimed) {
		busy = 0;
		reclaimed = 0;
		(void)vnode_iterate_reloadq(mp);
		/* returned with mount lock held */
		goto loop;
	}

	/* if new vnodes were created in between retry the reclaim */
 	if ( vnode_iterate_reloadq(mp) != 0) {
		if (!(busy && ((flags & FORCECLOSE)==0)))
			goto loop;
	}
	vnode_iterate_clear(mp);
	mount_unlock(mp);
	mount_iterate_unlock(mp);

	if (busy && ((flags & FORCECLOSE)==0))
		return (EBUSY);
	return (0);
}