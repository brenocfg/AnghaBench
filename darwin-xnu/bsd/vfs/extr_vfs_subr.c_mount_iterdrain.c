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
typedef  TYPE_1__* mount_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_3__ {int mnt_iterref; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVFS ; 
 int /*<<< orphan*/  mnt_list_mtx_lock ; 
 int /*<<< orphan*/  mount_list_lock () ; 
 int /*<<< orphan*/  mount_list_unlock () ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void
mount_iterdrain(mount_t mp)
{
	mount_list_lock();
	while (mp->mnt_iterref)
		msleep((caddr_t)&mp->mnt_iterref, mnt_list_mtx_lock, PVFS, "mount_iterdrain", NULL);
	/* mount iterations drained */
	mp->mnt_iterref = -1;
	mount_list_unlock();
}