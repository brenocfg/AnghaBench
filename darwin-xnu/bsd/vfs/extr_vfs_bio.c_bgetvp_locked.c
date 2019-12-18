#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  TYPE_2__* buf_t ;
struct TYPE_7__ {int /*<<< orphan*/  b_dev; TYPE_1__* b_vp; } ;
struct TYPE_6__ {scalar_t__ v_type; int /*<<< orphan*/  v_cleanblkhd; int /*<<< orphan*/  v_rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODEV ; 
 scalar_t__ VBLK ; 
 scalar_t__ VCHR ; 
 int /*<<< orphan*/  bufinsvn (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
bgetvp_locked(vnode_t vp, buf_t bp)
{

	if (bp->b_vp != vp)
		panic("bgetvp_locked: not free");

	if (vp->v_type == VBLK || vp->v_type == VCHR)
		bp->b_dev = vp->v_rdev;
	else
		bp->b_dev = NODEV;
	/*
	 * Insert onto list for new vnode.
	 */
	bufinsvn(bp, &vp->v_cleanblkhd);
}