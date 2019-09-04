#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vfsioattr {int /*<<< orphan*/  io_max_swappin_available; int /*<<< orphan*/  io_flags; int /*<<< orphan*/  io_devblocksize; int /*<<< orphan*/  io_maxsegwritesize; int /*<<< orphan*/  io_maxsegreadsize; int /*<<< orphan*/  io_segwritecnt; int /*<<< orphan*/  io_segreadcnt; int /*<<< orphan*/  io_maxwritecnt; int /*<<< orphan*/  io_maxreadcnt; } ;
typedef  TYPE_1__* mount_t ;
struct TYPE_3__ {int /*<<< orphan*/  mnt_max_swappin_available; int /*<<< orphan*/  mnt_ioflags; int /*<<< orphan*/  mnt_devblocksize; int /*<<< orphan*/  mnt_maxsegwritesize; int /*<<< orphan*/  mnt_maxsegreadsize; int /*<<< orphan*/  mnt_segwritecnt; int /*<<< orphan*/  mnt_segreadcnt; int /*<<< orphan*/  mnt_maxwritecnt; int /*<<< orphan*/  mnt_maxreadcnt; } ;

/* Variables and functions */

void 
vfs_setioattr(mount_t mp, struct vfsioattr * ioattrp)
{
        if (mp == NULL)
	        return;
        mp->mnt_maxreadcnt  = ioattrp->io_maxreadcnt;
	mp->mnt_maxwritecnt = ioattrp->io_maxwritecnt;
	mp->mnt_segreadcnt  = ioattrp->io_segreadcnt;
	mp->mnt_segwritecnt = ioattrp->io_segwritecnt;
	mp->mnt_maxsegreadsize = ioattrp->io_maxsegreadsize;
	mp->mnt_maxsegwritesize = ioattrp->io_maxsegwritesize;
	mp->mnt_devblocksize = ioattrp->io_devblocksize;
	mp->mnt_ioflags = ioattrp->io_flags;
	mp->mnt_max_swappin_available = ioattrp->io_max_swappin_available;
}