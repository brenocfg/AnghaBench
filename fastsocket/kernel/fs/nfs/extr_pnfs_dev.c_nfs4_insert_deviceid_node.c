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
struct nfs4_deviceid_node {int /*<<< orphan*/  ref; int /*<<< orphan*/  node; int /*<<< orphan*/  deviceid; int /*<<< orphan*/  nfs_client; int /*<<< orphan*/  ld; } ;

/* Variables and functions */
 struct nfs4_deviceid_node* _find_get_deviceid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nfs4_deviceid_cache ; 
 long nfs4_deviceid_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_deviceid_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nfs4_deviceid_node *
nfs4_insert_deviceid_node(struct nfs4_deviceid_node *new)
{
	struct nfs4_deviceid_node *d;
	long hash;

	spin_lock(&nfs4_deviceid_lock);
	hash = nfs4_deviceid_hash(&new->deviceid);
	d = _find_get_deviceid(new->ld, new->nfs_client, &new->deviceid, hash);
	if (d) {
		spin_unlock(&nfs4_deviceid_lock);
		return d;
	}

	hlist_add_head_rcu(&new->node, &nfs4_deviceid_cache[hash]);
	spin_unlock(&nfs4_deviceid_lock);
	atomic_inc(&new->ref);

	return new;
}