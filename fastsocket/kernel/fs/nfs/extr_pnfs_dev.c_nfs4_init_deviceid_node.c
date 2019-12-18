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
struct nfs4_deviceid {int dummy; } ;
struct nfs4_deviceid_node {int /*<<< orphan*/  ref; struct nfs4_deviceid deviceid; scalar_t__ flags; struct nfs_client const* nfs_client; struct pnfs_layoutdriver_type const* ld; int /*<<< orphan*/  tmpnode; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

void
nfs4_init_deviceid_node(struct nfs4_deviceid_node *d,
			const struct pnfs_layoutdriver_type *ld,
			const struct nfs_client *nfs_client,
			const struct nfs4_deviceid *id)
{
	INIT_HLIST_NODE(&d->node);
	INIT_HLIST_NODE(&d->tmpnode);
	d->ld = ld;
	d->nfs_client = nfs_client;
	d->flags = 0;
	d->deviceid = *id;
	atomic_set(&d->ref, 1);
}