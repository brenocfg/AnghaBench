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
struct TYPE_3__ {int /*<<< orphan*/  mnt_rwlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 

void
vfs_unbusy(mount_t mp)
{
	lck_rw_done(&mp->mnt_rwlock);
}