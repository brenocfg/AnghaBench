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
struct TYPE_3__ {int /*<<< orphan*/  mnt_rwlock; int /*<<< orphan*/  mnt_renamelock; int /*<<< orphan*/  mnt_iter_lock; int /*<<< orphan*/  mnt_mlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  lck_mtx_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_rw_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mnt_lck_grp ; 

void
mount_lock_destroy(mount_t mp)
{
	lck_mtx_destroy(&mp->mnt_mlock, mnt_lck_grp);
	lck_mtx_destroy(&mp->mnt_iter_lock, mnt_lck_grp);
	lck_mtx_destroy(&mp->mnt_renamelock, mnt_lck_grp);
	lck_rw_destroy(&mp->mnt_rwlock, mnt_lck_grp);
}