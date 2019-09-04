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
typedef  int /*<<< orphan*/  vnode_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  NULLVP ; 

int
vnode_getbackingvnode(vnode_t in_vp, vnode_t* out_vpp)
{
	if (out_vpp) {
		*out_vpp = NULLVP;
	}
#if NULLFS
	return nullfs_getbackingvnode(in_vp, out_vpp);
#else
#pragma unused(in_vp)
	return ENOENT;
#endif
}