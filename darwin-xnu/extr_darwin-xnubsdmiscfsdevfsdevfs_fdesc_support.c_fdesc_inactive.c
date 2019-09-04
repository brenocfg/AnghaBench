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
struct vnop_inactive_args {struct vnode* a_vp; } ;
struct vnode {int /*<<< orphan*/  v_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  VNON ; 

int
fdesc_inactive(struct vnop_inactive_args *ap)
{
	struct vnode *vp = ap->a_vp;

	/*
	 * Clear out the v_type field to avoid
	 * nasty things happening in vgone().
	 */
	vp->v_type = VNON;

	return (0);
}