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
struct pnfs_layoutdriver_type {int dummy; } ;
struct nfs_client {int dummy; } ;
struct nfs4_deviceid_node {int /*<<< orphan*/  ref; } ;
struct nfs4_deviceid {int dummy; } ;

/* Variables and functions */
 struct nfs4_deviceid_node* _lookup_deviceid (struct pnfs_layoutdriver_type const*,struct nfs_client const*,struct nfs4_deviceid const*,long) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

struct nfs4_deviceid_node *
_find_get_deviceid(const struct pnfs_layoutdriver_type *ld,
		   const struct nfs_client *clp, const struct nfs4_deviceid *id,
		   long hash)
{
	struct nfs4_deviceid_node *d;

	rcu_read_lock();
	d = _lookup_deviceid(ld, clp, id, hash);
	if (d != NULL)
		atomic_inc(&d->ref);
	rcu_read_unlock();
	return d;
}