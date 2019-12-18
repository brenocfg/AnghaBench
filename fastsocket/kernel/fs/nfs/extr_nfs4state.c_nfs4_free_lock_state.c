#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_server {int /*<<< orphan*/  lockowner_id; struct nfs_client* nfs_client; } ;
struct nfs_client {int /*<<< orphan*/  cl_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait; } ;
struct nfs4_lock_state {TYPE_1__ ls_sequence; int /*<<< orphan*/  ls_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfs4_lock_state*) ; 
 int /*<<< orphan*/  nfs_free_unique_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_destroy_wait_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs4_free_lock_state(struct nfs_server *server, struct nfs4_lock_state *lsp)
{
	struct nfs_client *clp = server->nfs_client;

	spin_lock(&clp->cl_lock);
	nfs_free_unique_id(&server->lockowner_id, &lsp->ls_id);
	spin_unlock(&clp->cl_lock);
	rpc_destroy_wait_queue(&lsp->ls_sequence.wait);
	kfree(lsp);
}