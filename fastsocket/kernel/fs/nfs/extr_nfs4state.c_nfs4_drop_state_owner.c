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
struct nfs_server {int /*<<< orphan*/  state_owners; struct nfs_client* nfs_client; } ;
struct nfs_client {int /*<<< orphan*/  cl_lock; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_server_node; struct nfs_server* so_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_CLEAR_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs4_drop_state_owner(struct nfs4_state_owner *sp)
{
	if (!RB_EMPTY_NODE(&sp->so_server_node)) {
		struct nfs_server *server = sp->so_server;
		struct nfs_client *clp = server->nfs_client;

		spin_lock(&clp->cl_lock);
		rb_erase(&sp->so_server_node, &server->state_owners);
		RB_CLEAR_NODE(&sp->so_server_node);
		spin_unlock(&clp->cl_lock);
	}
}