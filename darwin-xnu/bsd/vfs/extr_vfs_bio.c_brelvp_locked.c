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
typedef  scalar_t__ vnode_t ;
typedef  TYPE_2__* buf_t ;
struct TYPE_5__ {scalar_t__ le_next; } ;
struct TYPE_6__ {scalar_t__ b_vp; TYPE_1__ b_vnbufs; } ;

/* Variables and functions */
 scalar_t__ NOLIST ; 
 int /*<<< orphan*/  bufremvn (TYPE_2__*) ; 

__attribute__((used)) static void
brelvp_locked(buf_t bp)
{
	/*
	 * Delete from old vnode list, if on one.
	 */
	if (bp->b_vnbufs.le_next != NOLIST)
		bufremvn(bp);

	bp->b_vp = (vnode_t)NULL;
}