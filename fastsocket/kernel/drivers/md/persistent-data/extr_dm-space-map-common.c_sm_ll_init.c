#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int size; int /*<<< orphan*/ * equal; int /*<<< orphan*/ * dec; int /*<<< orphan*/ * inc; } ;
struct TYPE_8__ {int levels; TYPE_3__ value_type; struct dm_transaction_manager* tm; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * equal; int /*<<< orphan*/ * dec; int /*<<< orphan*/ * inc; } ;
struct TYPE_6__ {int levels; TYPE_1__ value_type; struct dm_transaction_manager* tm; } ;
struct ll_disk {int block_size; int entries_per_block; int bitmap_index_changed; scalar_t__ ref_count_root; scalar_t__ bitmap_root; scalar_t__ nr_blocks; TYPE_4__ ref_count_info; TYPE_2__ bitmap_info; struct dm_transaction_manager* tm; } ;
struct dm_transaction_manager {int dummy; } ;
struct disk_index_entry {int dummy; } ;
struct disk_bitmap_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int ENTRIES_PER_BYTE ; 
 int dm_bm_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_get_bm (struct dm_transaction_manager*) ; 

__attribute__((used)) static int sm_ll_init(struct ll_disk *ll, struct dm_transaction_manager *tm)
{
	ll->tm = tm;

	ll->bitmap_info.tm = tm;
	ll->bitmap_info.levels = 1;

	/*
	 * Because the new bitmap blocks are created via a shadow
	 * operation, the old entry has already had its reference count
	 * decremented and we don't need the btree to do any bookkeeping.
	 */
	ll->bitmap_info.value_type.size = sizeof(struct disk_index_entry);
	ll->bitmap_info.value_type.inc = NULL;
	ll->bitmap_info.value_type.dec = NULL;
	ll->bitmap_info.value_type.equal = NULL;

	ll->ref_count_info.tm = tm;
	ll->ref_count_info.levels = 1;
	ll->ref_count_info.value_type.size = sizeof(uint32_t);
	ll->ref_count_info.value_type.inc = NULL;
	ll->ref_count_info.value_type.dec = NULL;
	ll->ref_count_info.value_type.equal = NULL;

	ll->block_size = dm_bm_block_size(dm_tm_get_bm(tm));

	if (ll->block_size > (1 << 30)) {
		DMERR("block size too big to hold bitmaps");
		return -EINVAL;
	}

	ll->entries_per_block = (ll->block_size - sizeof(struct disk_bitmap_header)) *
		ENTRIES_PER_BYTE;
	ll->nr_blocks = 0;
	ll->bitmap_root = 0;
	ll->ref_count_root = 0;
	ll->bitmap_index_changed = false;

	return 0;
}