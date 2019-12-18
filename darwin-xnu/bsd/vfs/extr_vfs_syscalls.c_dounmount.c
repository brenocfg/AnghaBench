#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  struct vnode* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct vnode {scalar_t__ v_resolve; int /*<<< orphan*/  v_flag; struct mount* v_mountedhere; } ;
struct mount {int mnt_lflag; int mnt_flag; int /*<<< orphan*/  mnt_rwlock; int /*<<< orphan*/  mnt_triggerdata; int /*<<< orphan*/  (* mnt_triggercallback ) (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* mnt_vtable; int /*<<< orphan*/  mnt_crossref; struct vnode* mnt_vnodecovered; struct vnode* mnt_devvp; int /*<<< orphan*/  mnt_kern_flag; struct vnode* mnt_realrootvp; } ;
typedef  TYPE_2__* proc_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  p_flag; } ;
struct TYPE_5__ {int vfc_vfsflags; int /*<<< orphan*/  vfc_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int FORCECLOSE ; 
 int FREAD ; 
 int /*<<< orphan*/  FREE_ZONE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int FWRITE ; 
 int /*<<< orphan*/  IOBSDMountChange (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MNTK_UNMOUNT ; 
 int MNT_ASYNC ; 
 int MNT_FORCE ; 
 int MNT_LDEAD ; 
 int MNT_LFORCE ; 
 int MNT_LNOSUB ; 
 int MNT_LUNMOUNT ; 
 int MNT_LWAIT ; 
 int MNT_NOBLOCK ; 
 int MNT_RDONLY ; 
 int MNT_ROOTFS ; 
 int /*<<< orphan*/  MNT_WAIT ; 
 int /*<<< orphan*/  M_MOUNT ; 
 int /*<<< orphan*/  NOTE_WRITE ; 
 struct vnode* NULLVP ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSBitAndAtomic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int OSBitOrAtomic (int,int /*<<< orphan*/ *) ; 
 int P_NOREMOTEHANG ; 
 int SKIPROOT ; 
 int SKIPSWAP ; 
 int SKIPSYSTEM ; 
 int VFC_VFSLOCALARGS ; 
 int VFS_SYNC (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VFS_UNMOUNT (struct mount*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMOUNT ; 
 int /*<<< orphan*/  VNOP_CLOSE (struct vnode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VQ_UNMOUNT ; 
 int /*<<< orphan*/  VTC_RELEASE ; 
 int /*<<< orphan*/  VTC_REPLACE ; 
 int /*<<< orphan*/  cache_purgevfs (struct mount*) ; 
 int /*<<< orphan*/  disk_conditioner_unmount (struct mount*) ; 
 int /*<<< orphan*/  dounmount_submounts (struct mount*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsevent_unmount (struct mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kIOMountChangeUnmount ; 
 TYPE_2__* kernproc ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_vnode_and_post (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_mount_label_destroy (struct mount*) ; 
 int /*<<< orphan*/  mount_drop (struct mount*,int) ; 
 int /*<<< orphan*/  mount_dropcrossref (struct mount*,struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_generation ; 
 int /*<<< orphan*/  mount_iterdrain (struct mount*) ; 
 int /*<<< orphan*/  mount_iterreset (struct mount*) ; 
 int /*<<< orphan*/  mount_list_lock () ; 
 int /*<<< orphan*/  mount_list_remove (struct mount*) ; 
 int /*<<< orphan*/  mount_list_unlock () ; 
 int /*<<< orphan*/  mount_lock (struct mount*) ; 
 int /*<<< orphan*/  mount_lock_destroy (struct mount*) ; 
 int /*<<< orphan*/  mount_refdrain (struct mount*) ; 
 int /*<<< orphan*/  mount_unlock (struct mount*) ; 
 int /*<<< orphan*/  name_cache_lock () ; 
 int /*<<< orphan*/  name_cache_unlock () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stub1 (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mount*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubc_umount (struct mount*) ; 
 int vflush (struct mount*,struct vnode*,int) ; 
 TYPE_2__* vfs_context_proc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_event_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  vfs_nested_trigger_unmounts (struct mount*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_nummntops ; 
 int /*<<< orphan*/  vnode_clearmountedon (struct vnode*) ; 
 int /*<<< orphan*/  vnode_getalways (struct vnode*) ; 
 struct vnode* vnode_getparent (struct vnode*) ; 
 int /*<<< orphan*/  vnode_isrecycled (struct vnode*) ; 
 int /*<<< orphan*/  vnode_lock_spin (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int /*<<< orphan*/  vnode_rele (struct vnode*) ; 
 int /*<<< orphan*/  vnode_trigger_rearm (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

int
dounmount(struct mount *mp, int flags, int withref, vfs_context_t ctx)
{
	vnode_t coveredvp = (vnode_t)0;
	int error;
	int needwakeup = 0;
	int forcedunmount = 0;
	int lflags = 0;
	struct vnode *devvp = NULLVP;
#if CONFIG_TRIGGERS
	proc_t p = vfs_context_proc(ctx);
	int did_vflush = 0;
	int pflags_save = 0;
#endif /* CONFIG_TRIGGERS */

#if CONFIG_FSE
	if (!(flags & MNT_FORCE)) {
		fsevent_unmount(mp, ctx);  /* has to come first! */
	}
#endif

	mount_lock(mp);

	/*
	 * If already an unmount in progress just return EBUSY.
	 * Even a forced unmount cannot override.
	 */
	if (mp->mnt_lflag & MNT_LUNMOUNT) {
		if (withref != 0)
			mount_drop(mp, 1);
		mount_unlock(mp);
		return (EBUSY);
	}

	if (flags & MNT_FORCE) {
		forcedunmount = 1;
		mp->mnt_lflag |= MNT_LFORCE;
	}

#if CONFIG_TRIGGERS
	if (flags & MNT_NOBLOCK && p != kernproc)
		pflags_save = OSBitOrAtomic(P_NOREMOTEHANG, &p->p_flag);
#endif

	mp->mnt_kern_flag |= MNTK_UNMOUNT;
	mp->mnt_lflag |= MNT_LUNMOUNT;
	mp->mnt_flag &=~ MNT_ASYNC;
	/*
	 * anyone currently in the fast path that
	 * trips over the cached rootvp will be
	 * dumped out and forced into the slow path
	 * to regenerate a new cached value
	 */
	mp->mnt_realrootvp = NULLVP;
	mount_unlock(mp);

	if (forcedunmount && (flags & MNT_LNOSUB) == 0) {
		/*
		 * Force unmount any mounts in this filesystem.
		 * If any unmounts fail - just leave them dangling.
		 * Avoids recursion.
		 */
		(void) dounmount_submounts(mp, flags | MNT_LNOSUB, ctx);
	}

	/*
	 * taking the name_cache_lock exclusively will
	 * insure that everyone is out of the fast path who
	 * might be trying to use a now stale copy of
	 * vp->v_mountedhere->mnt_realrootvp
	 * bumping mount_generation causes the cached values
	 * to be invalidated
	 */
	name_cache_lock();
	mount_generation++;
	name_cache_unlock();


	lck_rw_lock_exclusive(&mp->mnt_rwlock);
	if (withref != 0)
		mount_drop(mp, 0);
	error = 0;
	if (forcedunmount == 0) {
		ubc_umount(mp);	/* release cached vnodes */
		if ((mp->mnt_flag & MNT_RDONLY) == 0) {
			error = VFS_SYNC(mp, MNT_WAIT, ctx);
			if (error) {
				mount_lock(mp);
				mp->mnt_kern_flag &= ~MNTK_UNMOUNT;
				mp->mnt_lflag &= ~MNT_LUNMOUNT;
				mp->mnt_lflag &= ~MNT_LFORCE;
				goto out;
			}
		}
	}

	/* free disk_conditioner_info structure for this mount */
	disk_conditioner_unmount(mp);

	IOBSDMountChange(mp, kIOMountChangeUnmount);

#if CONFIG_TRIGGERS
	vfs_nested_trigger_unmounts(mp, flags, ctx);
	did_vflush = 1;
#endif
	if (forcedunmount)
		lflags |= FORCECLOSE;
	error = vflush(mp, NULLVP, SKIPSWAP | SKIPSYSTEM  | SKIPROOT | lflags);
	if ((forcedunmount == 0) && error) {
		mount_lock(mp);
		mp->mnt_kern_flag &= ~MNTK_UNMOUNT;
		mp->mnt_lflag &= ~MNT_LUNMOUNT;
		mp->mnt_lflag &= ~MNT_LFORCE;
		goto out;
	}

	/* make sure there are no one in the mount iterations or lookup */
	mount_iterdrain(mp);

	error = VFS_UNMOUNT(mp, flags, ctx);
	if (error) {
		mount_iterreset(mp);
		mount_lock(mp);
		mp->mnt_kern_flag &= ~MNTK_UNMOUNT;
		mp->mnt_lflag &= ~MNT_LUNMOUNT;
		mp->mnt_lflag &= ~MNT_LFORCE;
		goto out;
	}

	/* increment the operations count */
	if (!error)
		OSAddAtomic(1, &vfs_nummntops);

	if ( mp->mnt_devvp && mp->mnt_vtable->vfc_vfsflags & VFC_VFSLOCALARGS) {
		/* hold an io reference and drop the usecount before close */
		devvp = mp->mnt_devvp;
		vnode_getalways(devvp);
		vnode_rele(devvp);
		VNOP_CLOSE(devvp, mp->mnt_flag & MNT_RDONLY ? FREAD : FREAD|FWRITE,
                       ctx);
		vnode_clearmountedon(devvp);
		vnode_put(devvp);
	}
	lck_rw_done(&mp->mnt_rwlock);
	mount_list_remove(mp);
	lck_rw_lock_exclusive(&mp->mnt_rwlock);

	/* mark the mount point hook in the vp but not drop the ref yet */
	if ((coveredvp = mp->mnt_vnodecovered) != NULLVP) {
		/*
		 * The covered vnode needs special handling. Trying to get an
		 * iocount must not block here as this may lead to deadlocks
		 * if the Filesystem to which the covered vnode belongs is
		 * undergoing forced unmounts. Since we hold a usecount, the
		 * vnode cannot be reused (it can, however, still be terminated)
		 */
		vnode_getalways(coveredvp);
		vnode_lock_spin(coveredvp);

		mp->mnt_crossref++;
		coveredvp->v_mountedhere = (struct mount *)0;
		CLR(coveredvp->v_flag, VMOUNT);

		vnode_unlock(coveredvp);
		vnode_put(coveredvp);
	}

	mount_list_lock();
	mp->mnt_vtable->vfc_refcount--;
	mount_list_unlock();

	cache_purgevfs(mp);	/* remove cache entries for this file sys */
	vfs_event_signal(NULL, VQ_UNMOUNT, (intptr_t)NULL);
	mount_lock(mp);
	mp->mnt_lflag |= MNT_LDEAD;

	if (mp->mnt_lflag & MNT_LWAIT) {
	        /*
		 * do the wakeup here
		 * in case we block in mount_refdrain
		 * which will drop the mount lock
		 * and allow anyone blocked in vfs_busy
		 * to wakeup and see the LDEAD state
		 */
		mp->mnt_lflag &= ~MNT_LWAIT;
		wakeup((caddr_t)mp);
	}
	mount_refdrain(mp);
out:
	if (mp->mnt_lflag & MNT_LWAIT) {
		mp->mnt_lflag &= ~MNT_LWAIT;
		needwakeup = 1;
	}

#if CONFIG_TRIGGERS
	if (flags & MNT_NOBLOCK && p != kernproc) {
	 	// Restore P_NOREMOTEHANG bit to its previous value
		if ((pflags_save & P_NOREMOTEHANG) == 0)
			OSBitAndAtomic(~((uint32_t) P_NOREMOTEHANG), &p->p_flag);
	}

	/*
	 * Callback and context are set together under the mount lock, and
	 * never cleared, so we're safe to examine them here, drop the lock,
	 * and call out.
	 */
	if (mp->mnt_triggercallback != NULL) {
		mount_unlock(mp);
		if (error == 0) {
			mp->mnt_triggercallback(mp, VTC_RELEASE, mp->mnt_triggerdata, ctx);
		} else if (did_vflush) {
			mp->mnt_triggercallback(mp, VTC_REPLACE, mp->mnt_triggerdata, ctx);
		}
	} else {
		mount_unlock(mp);
	}
#else
	mount_unlock(mp);
#endif /* CONFIG_TRIGGERS */

	lck_rw_done(&mp->mnt_rwlock);

	if (needwakeup)
		wakeup((caddr_t)mp);

	if (!error) {
		if ((coveredvp != NULLVP)) {
			vnode_t pvp = NULLVP;

			/*
			 * The covered vnode needs special handling. Trying to
			 * get an iocount must not block here as this may lead
			 * to deadlocks if the Filesystem to which the covered
			 * vnode belongs is undergoing forced unmounts. Since we
			 * hold a usecount, the  vnode cannot be reused
			 * (it can, however, still be terminated).
			 */
			vnode_getalways(coveredvp);

			mount_dropcrossref(mp, coveredvp, 0);
			/*
			 * We'll _try_ to detect if this really needs to be
			 * done. The coveredvp can only be in termination (or
			 * terminated) if the coveredvp's mount point is in a
			 * forced unmount (or has been) since we still hold the
			 * ref.
			 */
			if (!vnode_isrecycled(coveredvp)) {
				pvp = vnode_getparent(coveredvp);
#if CONFIG_TRIGGERS
				if (coveredvp->v_resolve) {
					vnode_trigger_rearm(coveredvp, ctx);
				}
#endif
			}

			vnode_rele(coveredvp);
			vnode_put(coveredvp);
			coveredvp = NULLVP;

			if (pvp) {
				lock_vnode_and_post(pvp, NOTE_WRITE);
				vnode_put(pvp);
			}
		} else if (mp->mnt_flag & MNT_ROOTFS) {
				mount_lock_destroy(mp);
#if CONFIG_MACF
				mac_mount_label_destroy(mp);
#endif
				FREE_ZONE((caddr_t)mp, sizeof (struct mount), M_MOUNT);
		} else
			panic("dounmount: no coveredvp");
	}
	return (error);
}