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
typedef  TYPE_1__* vnode_t ;
typedef  TYPE_2__* mount_t ;
struct TYPE_6__ {TYPE_1__* mnt_vnodecovered; } ;
struct TYPE_5__ {scalar_t__ v_type; TYPE_2__* v_mountedhere; } ;

/* Variables and functions */
 scalar_t__ VDIR ; 

mount_t 
vnode_mountedhere(vnode_t vp)
{
	mount_t mp;

	if ((vp->v_type == VDIR) && ((mp = vp->v_mountedhere) != NULL) &&
	    (mp->mnt_vnodecovered == vp))
		return (mp);
	else
		return (mount_t)NULL;
}