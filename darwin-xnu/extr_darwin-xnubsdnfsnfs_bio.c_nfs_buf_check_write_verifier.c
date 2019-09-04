#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct nfsmount {scalar_t__ nm_verf; } ;
struct nfsbuf {scalar_t__ nb_verf; int /*<<< orphan*/  nb_flags; } ;
typedef  TYPE_1__* nfsnode_t ;
struct TYPE_7__ {int /*<<< orphan*/  n_needcommitcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_NEEDCOMMITCNT (TYPE_1__*) ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ,int) ; 
 int NB_NEEDCOMMIT ; 
 int NB_STALEWVERF ; 
 struct nfsmount* NFSTONMP (TYPE_1__*) ; 
 scalar_t__ nfs_mount_gone (struct nfsmount*) ; 
 int /*<<< orphan*/  nfs_node_lock_force (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_node_unlock (TYPE_1__*) ; 

void
nfs_buf_check_write_verifier(nfsnode_t np, struct nfsbuf *bp)
{
	struct nfsmount *nmp;

	if (!ISSET(bp->nb_flags, NB_NEEDCOMMIT))
		return;

	nmp = NFSTONMP(np);
	if (nfs_mount_gone(nmp))
		return;
	if (!ISSET(bp->nb_flags, NB_STALEWVERF) && (bp->nb_verf == nmp->nm_verf))
		return;

	/* write verifier changed, clear commit/wverf flags */
	CLR(bp->nb_flags, (NB_NEEDCOMMIT | NB_STALEWVERF));
	bp->nb_verf = 0;
	nfs_node_lock_force(np);
	np->n_needcommitcnt--;
	CHECK_NEEDCOMMITCNT(np);
	nfs_node_unlock(np);
}