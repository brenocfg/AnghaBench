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
struct nfs_server {int /*<<< orphan*/  master_link; int /*<<< orphan*/  client_link; struct nfs_client* nfs_client; } ;
struct nfs_client {int /*<<< orphan*/  cl_res_state; int /*<<< orphan*/  cl_superblocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_CS_STOP_RENEW ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_client_lock ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void nfs_server_remove_lists(struct nfs_server *server)
{
	struct nfs_client *clp = server->nfs_client;

	spin_lock(&nfs_client_lock);
	list_del_rcu(&server->client_link);
	if (clp && list_empty(&clp->cl_superblocks))
		set_bit(NFS_CS_STOP_RENEW, &clp->cl_res_state);
	list_del(&server->master_link);
	spin_unlock(&nfs_client_lock);

	synchronize_rcu();
}