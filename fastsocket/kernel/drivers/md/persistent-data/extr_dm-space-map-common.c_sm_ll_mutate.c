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
typedef  int uint32_t ;
struct ll_disk {int (* load_ie ) (struct ll_disk*,int /*<<< orphan*/ ,struct disk_index_entry*) ;int (* save_ie ) (struct ll_disk*,int /*<<< orphan*/ ,struct disk_index_entry*) ;int /*<<< orphan*/  nr_allocated; int /*<<< orphan*/  ref_count_root; int /*<<< orphan*/  ref_count_info; int /*<<< orphan*/  tm; int /*<<< orphan*/  entries_per_block; } ;
struct dm_block {int dummy; } ;
struct disk_index_entry {void* none_free_before; int /*<<< orphan*/  nr_free; int /*<<< orphan*/  blocknr; } ;
typedef  enum allocation_event { ____Placeholder_allocation_event } allocation_event ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  void* __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int SM_ALLOC ; 
 int SM_FREE ; 
 int /*<<< orphan*/  __dm_bless_for_disk (void**) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 void* dm_bitmap_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int dm_btree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int dm_btree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_sm_bitmap_validator ; 
 int dm_tm_shadow_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**,int*) ; 
 int dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 
 int do_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int le32_to_cpu (void*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int sm_ll_lookup_big_ref_count (struct ll_disk*,int /*<<< orphan*/ ,int*) ; 
 int sm_lookup_bitmap (void*,int) ; 
 int /*<<< orphan*/  sm_set_bitmap (void*,int,int) ; 
 int stub1 (struct ll_disk*,int /*<<< orphan*/ ,struct disk_index_entry*) ; 
 int stub2 (struct ll_disk*,int /*<<< orphan*/ ,struct disk_index_entry*) ; 

__attribute__((used)) static int sm_ll_mutate(struct ll_disk *ll, dm_block_t b,
			int (*mutator)(void *context, uint32_t old, uint32_t *new),
			void *context, enum allocation_event *ev)
{
	int r;
	uint32_t bit, old, ref_count;
	struct dm_block *nb;
	dm_block_t index = b;
	struct disk_index_entry ie_disk;
	void *bm_le;
	int inc;

	bit = do_div(index, ll->entries_per_block);
	r = ll->load_ie(ll, index, &ie_disk);
	if (r < 0)
		return r;

	r = dm_tm_shadow_block(ll->tm, le64_to_cpu(ie_disk.blocknr),
			       &dm_sm_bitmap_validator, &nb, &inc);
	if (r < 0) {
		DMERR("dm_tm_shadow_block() failed");
		return r;
	}
	ie_disk.blocknr = cpu_to_le64(dm_block_location(nb));

	bm_le = dm_bitmap_data(nb);
	old = sm_lookup_bitmap(bm_le, bit);

	if (old > 2) {
		r = sm_ll_lookup_big_ref_count(ll, b, &old);
		if (r < 0) {
			dm_tm_unlock(ll->tm, nb);
			return r;
		}
	}

	r = mutator(context, old, &ref_count);
	if (r) {
		dm_tm_unlock(ll->tm, nb);
		return r;
	}

	if (ref_count <= 2) {
		sm_set_bitmap(bm_le, bit, ref_count);

		r = dm_tm_unlock(ll->tm, nb);
		if (r < 0)
			return r;

		if (old > 2) {
			r = dm_btree_remove(&ll->ref_count_info,
					    ll->ref_count_root,
					    &b, &ll->ref_count_root);
			if (r)
				return r;
		}

	} else {
		__le32 le_rc = cpu_to_le32(ref_count);

		sm_set_bitmap(bm_le, bit, 3);
		r = dm_tm_unlock(ll->tm, nb);
		if (r < 0)
			return r;

		__dm_bless_for_disk(&le_rc);
		r = dm_btree_insert(&ll->ref_count_info, ll->ref_count_root,
				    &b, &le_rc, &ll->ref_count_root);
		if (r < 0) {
			DMERR("ref count insert failed");
			return r;
		}
	}

	if (ref_count && !old) {
		*ev = SM_ALLOC;
		ll->nr_allocated++;
		le32_add_cpu(&ie_disk.nr_free, -1);
		if (le32_to_cpu(ie_disk.none_free_before) == bit)
			ie_disk.none_free_before = cpu_to_le32(bit + 1);

	} else if (old && !ref_count) {
		*ev = SM_FREE;
		ll->nr_allocated--;
		le32_add_cpu(&ie_disk.nr_free, 1);
		ie_disk.none_free_before = cpu_to_le32(min(le32_to_cpu(ie_disk.none_free_before), bit));
	}

	return ll->save_ie(ll, index, &ie_disk);
}