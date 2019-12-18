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
struct pnfs_layoutdriver_type {int dummy; } ;
struct nfs_client {int dummy; } ;
struct nfs4_deviceid_node {TYPE_1__* ld; int /*<<< orphan*/  ref; int /*<<< orphan*/  node; } ;
struct nfs4_deviceid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_deviceid_node ) (struct nfs4_deviceid_node*) ;} ;

/* Variables and functions */
 struct nfs4_deviceid_node* _lookup_deviceid (struct pnfs_layoutdriver_type const*,struct nfs_client const*,struct nfs4_deviceid const*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_deviceid_hash (struct nfs4_deviceid const*) ; 
 int /*<<< orphan*/  nfs4_deviceid_lock ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs4_deviceid_node*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void
nfs4_delete_deviceid(const struct pnfs_layoutdriver_type *ld,
			 const struct nfs_client *clp, const struct nfs4_deviceid *id)
{
	struct nfs4_deviceid_node *d;

	spin_lock(&nfs4_deviceid_lock);
	rcu_read_lock();
	d = _lookup_deviceid(ld, clp, id, nfs4_deviceid_hash(id));
	rcu_read_unlock();
	if (!d) {
		spin_unlock(&nfs4_deviceid_lock);
		return;
	}
	hlist_del_init_rcu(&d->node);
	spin_unlock(&nfs4_deviceid_lock);
	synchronize_rcu();

	/* balance the initial ref set in pnfs_insert_deviceid */
	if (atomic_dec_and_test(&d->ref))
		d->ld->free_deviceid_node(d);
}