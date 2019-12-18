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
struct vnode {scalar_t__ v_type; int v_specflags; scalar_t__ v_rdev; struct specinfo* v_specinfo; struct vnode* v_specnext; struct vnode** v_hashchain; } ;
struct specinfo {int dummy; } ;

/* Variables and functions */
 int DOCLOSE ; 
 int /*<<< orphan*/  FREE_ZONE (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SPECINFO ; 
 int SI_ALIASED ; 
 int /*<<< orphan*/  SPECHASH_LOCK () ; 
 int /*<<< orphan*/  SPECHASH_UNLOCK () ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  vclean (struct vnode*,int) ; 

__attribute__((used)) static void
vgone(vnode_t vp, int flags)
{
	struct vnode *vq;
	struct vnode *vx;

	/*
	 * Clean out the filesystem specific data.
	 * vclean also takes care of removing the
	 * vnode from any mount list it might be on
	 */
	vclean(vp, flags | DOCLOSE);

	/*
	 * If special device, remove it from special device alias list
	 * if it is on one.
	 */
	if ((vp->v_type == VBLK || vp->v_type == VCHR) && vp->v_specinfo != 0) {
			SPECHASH_LOCK();
			if (*vp->v_hashchain == vp) {
				*vp->v_hashchain = vp->v_specnext;
			} else {
				for (vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
					if (vq->v_specnext != vp)
						continue;
					vq->v_specnext = vp->v_specnext;
					break;
				}
			if (vq == NULL)
				panic("missing bdev");
			}
			if (vp->v_specflags & SI_ALIASED) {
				vx = NULL;
				for (vq = *vp->v_hashchain; vq; vq = vq->v_specnext) {
					if (vq->v_rdev != vp->v_rdev ||
				    	vq->v_type != vp->v_type)
						continue;
					if (vx)
						break;
					vx = vq;
				}
				if (vx == NULL)
					panic("missing alias");
				if (vq == NULL)
					vx->v_specflags &= ~SI_ALIASED;
				vp->v_specflags &= ~SI_ALIASED;
			}
			SPECHASH_UNLOCK();
			{
			struct specinfo *tmp = vp->v_specinfo;
			vp->v_specinfo = NULL;
			FREE_ZONE((void *)tmp, sizeof(struct specinfo), M_SPECINFO);
			}
	}
}