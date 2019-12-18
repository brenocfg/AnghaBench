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
struct nfs_server {int /*<<< orphan*/  state_owners_lru; struct nfs_client* nfs_client; } ;
struct nfs_client {int /*<<< orphan*/  cl_lock; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_lru; int /*<<< orphan*/  so_expires; int /*<<< orphan*/  so_server_node; int /*<<< orphan*/  so_count; struct nfs_server* so_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_free_state_owner (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  nfs4_remove_state_owner_locked (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs4_put_state_owner(struct nfs4_state_owner *sp)
{
	struct nfs_server *server = sp->so_server;
	struct nfs_client *clp = server->nfs_client;

	if (!atomic_dec_and_lock(&sp->so_count, &clp->cl_lock))
		return;

	if (!RB_EMPTY_NODE(&sp->so_server_node)) {
		sp->so_expires = jiffies;
		list_add_tail(&sp->so_lru, &server->state_owners_lru);
		spin_unlock(&clp->cl_lock);
	} else {
		nfs4_remove_state_owner_locked(sp);
		spin_unlock(&clp->cl_lock);
		nfs4_free_state_owner(sp);
	}
}