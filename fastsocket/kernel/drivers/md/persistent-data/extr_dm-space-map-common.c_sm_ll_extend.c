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
struct ll_disk {unsigned int nr_blocks; unsigned int (* max_entries ) (struct ll_disk*) ;int (* save_ie ) (struct ll_disk*,unsigned int,struct disk_index_entry*) ;int /*<<< orphan*/  entries_per_block; int /*<<< orphan*/  tm; } ;
struct dm_block {int dummy; } ;
struct disk_index_entry {scalar_t__ none_free_before; int /*<<< orphan*/  nr_free; int /*<<< orphan*/  blocknr; } ;
typedef  unsigned int dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 unsigned int dm_sector_div_up (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_sm_bitmap_validator ; 
 int dm_tm_new_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 
 unsigned int stub1 (struct ll_disk*) ; 
 int stub2 (struct ll_disk*,unsigned int,struct disk_index_entry*) ; 

int sm_ll_extend(struct ll_disk *ll, dm_block_t extra_blocks)
{
	int r;
	dm_block_t i, nr_blocks, nr_indexes;
	unsigned old_blocks, blocks;

	nr_blocks = ll->nr_blocks + extra_blocks;
	old_blocks = dm_sector_div_up(ll->nr_blocks, ll->entries_per_block);
	blocks = dm_sector_div_up(nr_blocks, ll->entries_per_block);

	nr_indexes = dm_sector_div_up(nr_blocks, ll->entries_per_block);
	if (nr_indexes > ll->max_entries(ll)) {
		DMERR("space map too large");
		return -EINVAL;
	}

	/*
	 * We need to set this before the dm_tm_new_block() call below.
	 */
	ll->nr_blocks = nr_blocks;
	for (i = old_blocks; i < blocks; i++) {
		struct dm_block *b;
		struct disk_index_entry idx;

		r = dm_tm_new_block(ll->tm, &dm_sm_bitmap_validator, &b);
		if (r < 0)
			return r;

		idx.blocknr = cpu_to_le64(dm_block_location(b));

		r = dm_tm_unlock(ll->tm, b);
		if (r < 0)
			return r;

		idx.nr_free = cpu_to_le32(ll->entries_per_block);
		idx.none_free_before = 0;

		r = ll->save_ie(ll, i, &idx);
		if (r < 0)
			return r;
	}

	return 0;
}