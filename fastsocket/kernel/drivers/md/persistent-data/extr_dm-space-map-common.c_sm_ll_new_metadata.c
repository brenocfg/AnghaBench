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
struct ll_disk {int (* init_index ) (struct ll_disk*) ;int /*<<< orphan*/  ref_count_root; int /*<<< orphan*/  ref_count_info; scalar_t__ nr_allocated; scalar_t__ nr_blocks; int /*<<< orphan*/  commit; int /*<<< orphan*/  max_entries; int /*<<< orphan*/  open_index; int /*<<< orphan*/  save_ie; int /*<<< orphan*/  load_ie; } ;
struct dm_transaction_manager {int dummy; } ;

/* Variables and functions */
 int dm_btree_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  metadata_ll_commit ; 
 int metadata_ll_init_index (struct ll_disk*) ; 
 int /*<<< orphan*/  metadata_ll_load_ie ; 
 int /*<<< orphan*/  metadata_ll_max_entries ; 
 int /*<<< orphan*/  metadata_ll_open ; 
 int /*<<< orphan*/  metadata_ll_save_ie ; 
 int sm_ll_init (struct ll_disk*,struct dm_transaction_manager*) ; 
 int stub1 (struct ll_disk*) ; 

int sm_ll_new_metadata(struct ll_disk *ll, struct dm_transaction_manager *tm)
{
	int r;

	r = sm_ll_init(ll, tm);
	if (r < 0)
		return r;

	ll->load_ie = metadata_ll_load_ie;
	ll->save_ie = metadata_ll_save_ie;
	ll->init_index = metadata_ll_init_index;
	ll->open_index = metadata_ll_open;
	ll->max_entries = metadata_ll_max_entries;
	ll->commit = metadata_ll_commit;

	ll->nr_blocks = 0;
	ll->nr_allocated = 0;

	r = ll->init_index(ll);
	if (r < 0)
		return r;

	r = dm_btree_empty(&ll->ref_count_info, &ll->ref_count_root);
	if (r < 0)
		return r;

	return 0;
}