#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  LCK_ATTR_NULL ; 
 int /*<<< orphan*/  LCK_GRP_ATTR_NULL ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_lock_lck_grp ; 
 int /*<<< orphan*/  nfs_lock_mutex ; 
 int /*<<< orphan*/  nfs_lockd_mount_list ; 
 int /*<<< orphan*/  nfs_pendlockq ; 

void
nfs_lockinit(void)
{
	TAILQ_INIT(&nfs_pendlockq);
	TAILQ_INIT(&nfs_lockd_mount_list);

	nfs_lock_lck_grp = lck_grp_alloc_init("nfs_lock", LCK_GRP_ATTR_NULL);
	nfs_lock_mutex = lck_mtx_alloc_init(nfs_lock_lck_grp, LCK_ATTR_NULL);
}