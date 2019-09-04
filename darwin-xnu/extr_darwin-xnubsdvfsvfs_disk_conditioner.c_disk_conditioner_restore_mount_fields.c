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
struct saved_mount_fields {int /*<<< orphan*/  mnt_ioscale; int /*<<< orphan*/  mnt_ioqueue_depth; int /*<<< orphan*/  mnt_segwritecnt; int /*<<< orphan*/  mnt_segreadcnt; int /*<<< orphan*/  mnt_maxwritecnt; int /*<<< orphan*/  mnt_maxreadcnt; } ;
typedef  TYPE_1__* mount_t ;
struct TYPE_3__ {int /*<<< orphan*/  mnt_ioscale; int /*<<< orphan*/  mnt_ioqueue_depth; int /*<<< orphan*/  mnt_segwritecnt; int /*<<< orphan*/  mnt_segreadcnt; int /*<<< orphan*/  mnt_maxwritecnt; int /*<<< orphan*/  mnt_maxreadcnt; } ;

/* Variables and functions */

__attribute__((used)) static inline void
disk_conditioner_restore_mount_fields(mount_t mp, struct saved_mount_fields *mnt_fields) {
	mp->mnt_maxreadcnt = mnt_fields->mnt_maxreadcnt;
	mp->mnt_maxwritecnt = mnt_fields->mnt_maxwritecnt;
	mp->mnt_segreadcnt = mnt_fields->mnt_segreadcnt;
	mp->mnt_segwritecnt = mnt_fields->mnt_segwritecnt;
	mp->mnt_ioqueue_depth = mnt_fields->mnt_ioqueue_depth;
	mp->mnt_ioscale = mnt_fields->mnt_ioscale;
}