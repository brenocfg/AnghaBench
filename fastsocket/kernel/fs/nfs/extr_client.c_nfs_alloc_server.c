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
struct nfs_server {int /*<<< orphan*/  io_stats; int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  active; int /*<<< orphan*/  state_owners_lru; int /*<<< orphan*/  layouts; int /*<<< orphan*/  delegations; int /*<<< orphan*/  master_link; int /*<<< orphan*/  client_link; int /*<<< orphan*/  client_acl; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bdi_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfs_server*) ; 
 struct nfs_server* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_alloc_iostats () ; 
 int /*<<< orphan*/  nfs_free_iostats (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pnfs_init_server (struct nfs_server*) ; 

__attribute__((used)) static struct nfs_server *nfs_alloc_server(void)
{
	struct nfs_server *server;

	server = kzalloc(sizeof(struct nfs_server), GFP_KERNEL);
	if (!server)
		return NULL;

	server->client = server->client_acl = ERR_PTR(-EINVAL);

	/* Zero out the NFS state stuff */
	INIT_LIST_HEAD(&server->client_link);
	INIT_LIST_HEAD(&server->master_link);
	INIT_LIST_HEAD(&server->delegations);
	INIT_LIST_HEAD(&server->layouts);
	INIT_LIST_HEAD(&server->state_owners_lru);

	atomic_set(&server->active, 0);

	server->io_stats = nfs_alloc_iostats();
	if (!server->io_stats) {
		kfree(server);
		return NULL;
	}

	if (bdi_init(&server->backing_dev_info)) {
		nfs_free_iostats(server->io_stats);
		kfree(server);
		return NULL;
	}

	pnfs_init_server(server);

	return server;
}