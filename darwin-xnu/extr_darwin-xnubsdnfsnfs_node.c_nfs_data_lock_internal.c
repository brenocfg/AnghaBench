#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_6__ {int /*<<< orphan*/  n_datalockowner; int /*<<< orphan*/  n_flag; int /*<<< orphan*/  n_datalock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSDBG_BOT (int,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NFS_DATA_LOCK_SHARED ; 
 int /*<<< orphan*/  NUPDATESIZE ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_data_update_size (TYPE_1__*,int) ; 

void
nfs_data_lock_internal(nfsnode_t np, int locktype, int updatesize)
{
	FSDBG_TOP(270, np, locktype, np->n_datalockowner, 0);
	if (locktype == NFS_DATA_LOCK_SHARED) {
		if (updatesize && ISSET(np->n_flag, NUPDATESIZE))
			nfs_data_update_size(np, 0);
		lck_rw_lock_shared(&np->n_datalock);
	} else {
		lck_rw_lock_exclusive(&np->n_datalock);
		np->n_datalockowner = current_thread();
		if (updatesize && ISSET(np->n_flag, NUPDATESIZE))
			nfs_data_update_size(np, 1);
	}
	FSDBG_BOT(270, np, locktype, np->n_datalockowner, 0);
}