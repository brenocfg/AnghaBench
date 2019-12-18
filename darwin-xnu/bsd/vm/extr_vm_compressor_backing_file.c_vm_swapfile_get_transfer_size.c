#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vnode_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {TYPE_2__* v_mount; } ;
struct TYPE_5__ {scalar_t__ f_iosize; } ;
struct TYPE_6__ {TYPE_1__ mnt_vfsstat; } ;

/* Variables and functions */

uint64_t
vm_swapfile_get_transfer_size(vnode_t vp)
{
	return((uint64_t)vp->v_mount->mnt_vfsstat.f_iosize);
}