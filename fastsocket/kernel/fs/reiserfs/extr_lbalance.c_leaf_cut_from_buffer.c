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
struct item_head {int dummy; } ;
struct disk_child {int dummy; } ;
struct buffer_info {scalar_t__ bi_parent; int /*<<< orphan*/  tb; int /*<<< orphan*/  bi_position; struct buffer_head* bi_bh; } ;
struct buffer_head {int b_size; scalar_t__ b_data; } ;
struct block_head {int dummy; } ;

/* Variables and functions */
 struct block_head* B_BLK_HEAD (struct buffer_head*) ; 
 int /*<<< orphan*/  B_I_DEH (struct buffer_head*,struct item_head*) ; 
 struct disk_child* B_N_CHILD (scalar_t__,int /*<<< orphan*/ ) ; 
 struct item_head* B_N_PITEM_HEAD (struct buffer_head*,int) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int UNFM_P_SIZE ; 
 scalar_t__ blkh_free_space (struct block_head*) ; 
 int blkh_nr_item (struct block_head*) ; 
 scalar_t__ dc_size (struct disk_child*) ; 
 scalar_t__ deh_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_balance_mark_internal_dirty (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_balance_mark_leaf_dirty (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_ih_free_space (struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 int ih_location (struct item_head*) ; 
 scalar_t__ is_direct_le_ih (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 int /*<<< orphan*/  is_statdata_le_ih (struct item_head*) ; 
 scalar_t__ le_ih_k_offset (struct item_head*) ; 
 int leaf_cut_entries (struct buffer_head*,struct item_head*,int,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  put_dc_size (struct disk_child*,scalar_t__) ; 
 int /*<<< orphan*/  put_ih_item_len (struct item_head*,int) ; 
 int /*<<< orphan*/  put_ih_location (struct item_head*,int) ; 
 int /*<<< orphan*/  set_blkh_free_space (struct block_head*,scalar_t__) ; 
 int /*<<< orphan*/  set_ih_free_space (struct item_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_le_ih_k_offset (struct item_head*,scalar_t__) ; 

void leaf_cut_from_buffer(struct buffer_info *bi, int cut_item_num,
			  int pos_in_item, int cut_size)
{
	int nr;
	struct buffer_head *bh = bi->bi_bh;
	struct block_head *blkh;
	struct item_head *ih;
	int last_loc, unmoved_loc;
	int i;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);

	/* item head of truncated item */
	ih = B_N_PITEM_HEAD(bh, cut_item_num);

	if (is_direntry_le_ih(ih)) {
		/* first cut entry () */
		cut_size = leaf_cut_entries(bh, ih, pos_in_item, cut_size);
		if (pos_in_item == 0) {
			/* change key */
			RFALSE(cut_item_num,
			       "when 0-th enrty of item is cut, that item must be first in the node, not %d-th",
			       cut_item_num);
			/* change item key by key of first entry in the item */
			set_le_ih_k_offset(ih, deh_offset(B_I_DEH(bh, ih)));
			/*memcpy (&ih->ih_key.k_offset, &(B_I_DEH (bh, ih)->deh_offset), SHORT_KEY_SIZE); */
		}
	} else {
		/* item is direct or indirect */
		RFALSE(is_statdata_le_ih(ih), "10195: item is stat data");
		RFALSE(pos_in_item && pos_in_item + cut_size != ih_item_len(ih),
		       "10200: invalid offset (%lu) or trunc_size (%lu) or ih_item_len (%lu)",
		       (long unsigned)pos_in_item, (long unsigned)cut_size,
		       (long unsigned)ih_item_len(ih));

		/* shift item body to left if cut is from the head of item */
		if (pos_in_item == 0) {
			memmove(bh->b_data + ih_location(ih),
				bh->b_data + ih_location(ih) + cut_size,
				ih_item_len(ih) - cut_size);

			/* change key of item */
			if (is_direct_le_ih(ih))
				set_le_ih_k_offset(ih,
						   le_ih_k_offset(ih) +
						   cut_size);
			else {
				set_le_ih_k_offset(ih,
						   le_ih_k_offset(ih) +
						   (cut_size / UNFM_P_SIZE) *
						   bh->b_size);
				RFALSE(ih_item_len(ih) == cut_size
				       && get_ih_free_space(ih),
				       "10205: invalid ih_free_space (%h)", ih);
			}
		}
	}

	/* location of the last item */
	last_loc = ih_location(&(ih[nr - cut_item_num - 1]));

	/* location of the item, which is remaining at the same place */
	unmoved_loc = cut_item_num ? ih_location(ih - 1) : bh->b_size;

	/* shift */
	memmove(bh->b_data + last_loc + cut_size, bh->b_data + last_loc,
		unmoved_loc - last_loc - cut_size);

	/* change item length */
	put_ih_item_len(ih, ih_item_len(ih) - cut_size);

	if (is_indirect_le_ih(ih)) {
		if (pos_in_item)
			set_ih_free_space(ih, 0);
	}

	/* change locations */
	for (i = cut_item_num; i < nr; i++)
		put_ih_location(&(ih[i - cut_item_num]),
				ih_location(&ih[i - cut_item_num]) + cut_size);

	/* size, free space */
	set_blkh_free_space(blkh, blkh_free_space(blkh) + cut_size);

	do_balance_mark_leaf_dirty(bi->tb, bh, 0);

	if (bi->bi_parent) {
		struct disk_child *t_dc;
		t_dc = B_N_CHILD(bi->bi_parent, bi->bi_position);
		put_dc_size(t_dc, dc_size(t_dc) - cut_size);
		do_balance_mark_internal_dirty(bi->tb, bi->bi_parent, 0);
	}
}