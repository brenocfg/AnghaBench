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
struct vnode {int v_lflag; int /*<<< orphan*/  v_lock; int /*<<< orphan*/  v_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVFS ; 
 int VL_LABEL ; 
 int VL_LABELED ; 
 int VL_LABELWAIT ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
vnode_relabel(struct vnode *vp)
{

	/* Wait for any other labeling to complete. */
	while (vp->v_lflag & VL_LABEL) {
		vp->v_lflag |= VL_LABELWAIT;
		(void)msleep(&vp->v_label, &vp->v_lock, PVFS, "vnode_relabel", 0);
	}

	/* Clear labeled flag */
	vp->v_lflag &= ~VL_LABELED;

	return;
}