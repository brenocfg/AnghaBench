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
struct TYPE_6__ {int /*<<< orphan*/ * n_datalockowner; int /*<<< orphan*/  n_flag; int /*<<< orphan*/  n_datalock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSDBG_BOT (int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUPDATESIZE ; 
 int /*<<< orphan*/ * current_thread () ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_data_update_size (TYPE_1__*,int) ; 

void
nfs_data_unlock_internal(nfsnode_t np, int updatesize)
{
	int mine = (np->n_datalockowner == current_thread());
	FSDBG_TOP(271, np, np->n_datalockowner, current_thread(), 0);
	if (updatesize && mine && ISSET(np->n_flag, NUPDATESIZE))
		nfs_data_update_size(np, 1);
	np->n_datalockowner = NULL;
	lck_rw_done(&np->n_datalock);
	if (updatesize && !mine && ISSET(np->n_flag, NUPDATESIZE))
		nfs_data_update_size(np, 0);
	FSDBG_BOT(271, np, np->n_datalockowner, current_thread(), 0);
}