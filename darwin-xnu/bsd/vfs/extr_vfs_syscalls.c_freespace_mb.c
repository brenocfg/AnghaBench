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
typedef  TYPE_2__* vnode_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_5__ {int f_bsize; scalar_t__ f_bavail; } ;
struct TYPE_7__ {TYPE_1__ mnt_vfsstat; } ;
struct TYPE_6__ {TYPE_3__* v_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFS_USER_EVENT ; 
 int /*<<< orphan*/  vfs_context_current () ; 
 int /*<<< orphan*/  vfs_update_vfsstat (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint32_t
freespace_mb(vnode_t vp)
{
	vfs_update_vfsstat(vp->v_mount, vfs_context_current(), VFS_USER_EVENT);
 	return (((uint64_t)vp->v_mount->mnt_vfsstat.f_bavail *
 	        vp->v_mount->mnt_vfsstat.f_bsize) >> 20);
}