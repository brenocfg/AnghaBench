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
struct nfs4_pnfs_ds {int /*<<< orphan*/  ds_node; int /*<<< orphan*/  ds_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  deviceid; } ;
struct nfs4_file_layout_dsaddr {int ds_num; struct nfs4_file_layout_dsaddr* stripe_indices; struct nfs4_pnfs_ds** ds_list; TYPE_1__ id_node; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_ds (struct nfs4_pnfs_ds*) ; 
 int /*<<< orphan*/  kfree (struct nfs4_file_layout_dsaddr*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_ds_cache_lock ; 
 int /*<<< orphan*/  nfs4_print_deviceid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
nfs4_fl_free_deviceid(struct nfs4_file_layout_dsaddr *dsaddr)
{
	struct nfs4_pnfs_ds *ds;
	int i;

	nfs4_print_deviceid(&dsaddr->id_node.deviceid);

	for (i = 0; i < dsaddr->ds_num; i++) {
		ds = dsaddr->ds_list[i];
		if (ds != NULL) {
			if (atomic_dec_and_lock(&ds->ds_count,
						&nfs4_ds_cache_lock)) {
				list_del_init(&ds->ds_node);
				spin_unlock(&nfs4_ds_cache_lock);
				destroy_ds(ds);
			}
		}
	}
	kfree(dsaddr->stripe_indices);
	kfree(dsaddr);
}