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
typedef  int uint32_t ;
struct vnode {scalar_t__ v_usecount; scalar_t__ v_kusecount; } ;

/* Variables and functions */

uint32_t
vnode_pager_isinuse(struct vnode *vp)
{
	if (vp->v_usecount > vp->v_kusecount)
		return (1);
	return (0);
}