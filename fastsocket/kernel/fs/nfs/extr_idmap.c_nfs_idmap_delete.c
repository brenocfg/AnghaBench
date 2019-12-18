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
struct nfs_client {struct idmap* cl_idmap; } ;
struct idmap {int /*<<< orphan*/  idmap_group_hash; int /*<<< orphan*/  idmap_user_hash; int /*<<< orphan*/  idmap_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  idmap_free_hashtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct idmap*) ; 
 int /*<<< orphan*/  rpc_unlink (int /*<<< orphan*/ ) ; 

void
nfs_idmap_delete(struct nfs_client *clp)
{
	struct idmap *idmap = clp->cl_idmap;

	if (!idmap)
		return;
	rpc_unlink(idmap->idmap_dentry);
	clp->cl_idmap = NULL;
	idmap_free_hashtable(&idmap->idmap_user_hash);
	idmap_free_hashtable(&idmap->idmap_group_hash);
	kfree(idmap);
}