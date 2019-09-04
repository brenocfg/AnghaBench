#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  scalar_t__ uint32_t ;
struct nameidata {TYPE_1__* ni_vp; } ;
struct componentname {int cn_flags; } ;
typedef  TYPE_2__* mount_t ;
struct TYPE_16__ {int mnt_generation; TYPE_1__* mnt_realrootvp; int /*<<< orphan*/  mnt_realrootvp_vid; int /*<<< orphan*/  mnt_lflag; int /*<<< orphan*/  mnt_crossref; } ;
struct TYPE_15__ {scalar_t__ v_type; int /*<<< orphan*/  v_id; TYPE_2__* v_mountedhere; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LK_NOWAIT ; 
 int /*<<< orphan*/  MNT_LFORCE ; 
 int NOCROSSMOUNT ; 
 scalar_t__ VDIR ; 
 int VFS_ROOT (TYPE_2__*,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_dropcrossref (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mount_generation ; 
 int /*<<< orphan*/  mount_lock_spin (TYPE_2__*) ; 
 int /*<<< orphan*/  mount_unlock (TYPE_2__*) ; 
 scalar_t__ vfs_busy (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vfs_unbusy (TYPE_2__*) ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_put (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

__attribute__((used)) static int
lookup_traverse_mountpoints(struct nameidata *ndp, struct componentname *cnp, vnode_t dp, 
		int vbusyflags, vfs_context_t ctx)
{
	mount_t mp;
	vnode_t tdp;
	int error = 0;
	uint32_t depth = 0;
	vnode_t	mounted_on_dp;
	int current_mount_generation = 0;
#if CONFIG_TRIGGERS
	vnode_t triggered_dp = NULLVP;
	int retry_cnt = 0;
#define MAX_TRIGGER_RETRIES 1
#endif
	
	if (dp->v_type != VDIR || cnp->cn_flags & NOCROSSMOUNT)
		return 0;

	mounted_on_dp = dp;
#if CONFIG_TRIGGERS
restart:
#endif
	current_mount_generation = mount_generation;

	while (dp->v_mountedhere) {
		vnode_lock_spin(dp);
		if ((mp = dp->v_mountedhere)) {
			mp->mnt_crossref++;
			vnode_unlock(dp);
		} else {
			vnode_unlock(dp);
			break;
		}

		if (ISSET(mp->mnt_lflag, MNT_LFORCE)) {
			mount_dropcrossref(mp, dp, 0);
			break;	// don't traverse into a forced unmount
		}


		if (vfs_busy(mp, vbusyflags)) {
			mount_dropcrossref(mp, dp, 0);
			if (vbusyflags == LK_NOWAIT) {
				error = ENOENT;
				goto out;
			}

			continue;
		}

		error = VFS_ROOT(mp, &tdp, ctx);

		mount_dropcrossref(mp, dp, 0);
		vfs_unbusy(mp);

		if (error) {
			goto out;
		}

		vnode_put(dp);
		ndp->ni_vp = dp = tdp;
		if (dp->v_type != VDIR) {
#if DEVELOPMENT || DEBUG
			panic("%s : Root of filesystem not a directory\n",
			    __FUNCTION__);
#else
			break;
#endif
		}
		depth++;
	}

#if CONFIG_TRIGGERS
	/*
	 * The triggered_dp check here is required but is susceptible to a
	 * (unlikely) race in which trigger mount is done from here and is
	 * unmounted before we get past vfs_busy above. We retry to deal with
	 * that case but it has the side effect of unwanted retries for
	 * "special" processes which don't want to trigger mounts.
	 */
	if (dp->v_resolve && retry_cnt < MAX_TRIGGER_RETRIES) {
		error = vnode_trigger_resolve(dp, ndp, ctx);
		if (error)
			goto out;
		if (dp == triggered_dp)
			retry_cnt += 1;
		else
			retry_cnt = 0;
		triggered_dp = dp;
		goto restart;
	}
#endif /* CONFIG_TRIGGERS */

	if (depth) {
	        mp = mounted_on_dp->v_mountedhere;

		if (mp) {
		        mount_lock_spin(mp);
			mp->mnt_realrootvp_vid = dp->v_id;
			mp->mnt_realrootvp = dp;
			mp->mnt_generation = current_mount_generation;
			mount_unlock(mp);
		}
	}

	return 0;

out:
	return error;
}