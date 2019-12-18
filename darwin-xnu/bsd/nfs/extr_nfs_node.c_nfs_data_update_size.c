#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_10__ {scalar_t__ n_newsize; scalar_t__ n_size; int /*<<< orphan*/  n_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSDBG_BOT (int,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FSDBG_TOP (int,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFSTOV (TYPE_1__*) ; 
 int /*<<< orphan*/  NFS_DATA_LOCK_EXCLUSIVE ; 
 int /*<<< orphan*/  NNEEDINVALIDATE ; 
 int /*<<< orphan*/  NUPDATESIZE ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_data_unlock (TYPE_1__*) ; 
 int nfs_node_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  ubc_setsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nfs_data_update_size(nfsnode_t np, int datalocked)
{
	int error;

	FSDBG_TOP(272, np, np->n_flag, np->n_size, np->n_newsize);
	if (!datalocked) {
		nfs_data_lock(np, NFS_DATA_LOCK_EXCLUSIVE);
		/* grabbing data lock will automatically update size */
		nfs_data_unlock(np);
		FSDBG_BOT(272, np, np->n_flag, np->n_size, np->n_newsize);
		return;
	}
	error = nfs_node_lock(np);
	if (error || !ISSET(np->n_flag, NUPDATESIZE)) {
		if (!error)
			nfs_node_unlock(np);
		FSDBG_BOT(272, np, np->n_flag, np->n_size, np->n_newsize);
		return;
	}
	CLR(np->n_flag, NUPDATESIZE);
	np->n_size = np->n_newsize;
	/* make sure we invalidate buffers the next chance we get */
	SET(np->n_flag, NNEEDINVALIDATE);
	nfs_node_unlock(np);
	ubc_setsize(NFSTOV(np), (off_t)np->n_size); /* XXX error? */
	FSDBG_BOT(272, np, np->n_flag, np->n_size, np->n_newsize);
}