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
struct TYPE_4__ {scalar_t__ lh_first; } ;
struct TYPE_5__ {TYPE_1__ v_cleanblkhd; } ;

/* Variables and functions */

int
vnode_hascleanblks(vnode_t vp)
{
	/*
	 * Not taking the buf_mtxp as there is little
	 * point doing it. Even if the lock is taken the
	 * state can change right after that. If their 
	 * needs to be a synchronization, it must be driven
	 * by the caller
	 */ 
        if (vp->v_cleanblkhd.lh_first)
	        return (1);
	return (0);
}