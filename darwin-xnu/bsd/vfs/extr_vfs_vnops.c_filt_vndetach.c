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
struct vnode {int /*<<< orphan*/  v_knotes; } ;
struct knote {int /*<<< orphan*/  kn_hookid; scalar_t__ kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int /*<<< orphan*/  VNODE_MONITOR_END ; 
 int /*<<< orphan*/  VNOP_MONITOR (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 scalar_t__ vnode_getwithvid (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

__attribute__((used)) static void
filt_vndetach(struct knote *kn)
{
	vfs_context_t ctx = vfs_context_current();
	struct vnode *vp; 
	vp = (struct vnode *)kn->kn_hook;
	if (vnode_getwithvid(vp, kn->kn_hookid))
		return;

	vnode_lock(vp);
	KNOTE_DETACH(&vp->v_knotes, kn);
	vnode_unlock(vp);
	
	/* 
	 * Tell a (generally networked) filesystem that we're no longer watching 
	 * If the FS wants to track contexts, it should still be using the one from
	 * the VNODE_MONITOR_BEGIN.
	 */
	VNOP_MONITOR(vp, 0, VNODE_MONITOR_END, (void*)kn, ctx);
	vnode_put(vp);
}