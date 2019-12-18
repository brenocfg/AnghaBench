#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vnode_t ;
struct TYPE_5__ {TYPE_1__* v_mount; } ;
struct TYPE_4__ {int mnt_flag; } ;

/* Variables and functions */
 int MNT_RDONLY ; 

int 
vnode_vfsisrdonly(vnode_t vp)
{
	return ((vp->v_mount->mnt_flag & MNT_RDONLY)? 1 : 0);
}