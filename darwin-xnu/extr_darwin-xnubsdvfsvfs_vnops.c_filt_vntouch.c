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
typedef  struct vnode* vnode_t ;
struct vnode {int dummy; } ;
struct knote {int /*<<< orphan*/  kn_sfflags; int /*<<< orphan*/  kn_hookid; scalar_t__ kn_hook; } ;
struct kevent_internal_s {int /*<<< orphan*/  fflags; } ;

/* Variables and functions */
 int NOTE_REVOKE ; 
 int VNODE_NODEAD ; 
 int VNODE_WITHID ; 
 int filt_vnode_common (struct knote*,struct vnode*,int) ; 
 scalar_t__ vnode_getiocount (struct vnode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnode_lock (struct vnode*) ; 
 int /*<<< orphan*/  vnode_put_locked (struct vnode*) ; 
 int /*<<< orphan*/  vnode_unlock (struct vnode*) ; 

__attribute__((used)) static int
filt_vntouch(struct knote *kn, struct kevent_internal_s *kev)
{
	vnode_t vp = (struct vnode *)kn->kn_hook;
	int activate;
	int hint = 0;

	vnode_lock(vp);
	if (vnode_getiocount(vp, kn->kn_hookid, VNODE_NODEAD | VNODE_WITHID) != 0) {
		/* is recycled */
		hint = NOTE_REVOKE;
	}

	/* accept new input fflags mask */
	kn->kn_sfflags = kev->fflags;

	activate = filt_vnode_common(kn, vp, hint);

	if (hint == 0)
		vnode_put_locked(vp);
	vnode_unlock(vp);

	return activate;
}