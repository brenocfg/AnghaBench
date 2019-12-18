#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vnop_pagein_args {int /*<<< orphan*/  a_flags; int /*<<< orphan*/  a_size; int /*<<< orphan*/  a_f_offset; int /*<<< orphan*/  a_pl_offset; int /*<<< orphan*/  a_pl; TYPE_4__* a_vp; } ;
typedef  TYPE_2__* mockfs_mount_t ;
typedef  TYPE_3__* mockfs_fsnode_t ;
struct TYPE_8__ {scalar_t__ v_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  size; TYPE_1__* mnt; } ;
struct TYPE_6__ {scalar_t__ mockfs_memory_backed; } ;
struct TYPE_5__ {scalar_t__ mnt_data; } ;

/* Variables and functions */
 int cluster_pagein (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

int mockfs_pagein(struct vnop_pagein_args * ap)
{
	mockfs_fsnode_t fsnode;
	mockfs_mount_t mockfs_mnt;

	/*
	 * Nothing special needed from us; just nab the filesize and kick the work over to cluster_pagein.
	 */
	fsnode = (mockfs_fsnode_t) ap->a_vp->v_data;
	mockfs_mnt = ((mockfs_mount_t) fsnode->mnt->mnt_data);	

	/*
	 * If we represent a memory backed device, we should be pointing directly to the backing store; we should never
	 *   see a pagein in this case.
	 */
	if (mockfs_mnt->mockfs_memory_backed)
		panic("mockfs_pagein called for a memory-backed device");

	return cluster_pagein(ap->a_vp, ap->a_pl, ap->a_pl_offset, ap->a_f_offset, ap->a_size, fsnode->size, ap->a_flags);	
}