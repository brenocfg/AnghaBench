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
struct buffer_head {int b_size; struct item_head* b_data; } ;
struct block_head {int dummy; } ;

/* Variables and functions */
 struct block_head* B_BLK_HEAD (struct buffer_head*) ; 
 struct disk_child* B_N_CHILD (scalar_t__,int /*<<< orphan*/ ) ; 
 struct item_head* B_N_PITEM_HEAD (struct buffer_head*,int) ; 
 int IH_SIZE ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 scalar_t__ blkh_free_space (struct block_head*) ; 
 int blkh_nr_item (struct block_head*) ; 
 scalar_t__ dc_size (struct disk_child*) ; 
 int /*<<< orphan*/  do_balance_mark_internal_dirty (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_balance_mark_leaf_dirty (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ih_location (struct item_head*) ; 
 int /*<<< orphan*/  make_empty_node (struct buffer_info*) ; 
 int /*<<< orphan*/  memmove (struct item_head*,struct item_head*,int) ; 
 int /*<<< orphan*/  put_dc_size (struct disk_child*,scalar_t__) ; 
 int /*<<< orphan*/  put_ih_location (struct item_head*,int) ; 
 int /*<<< orphan*/  set_blkh_free_space (struct block_head*,scalar_t__) ; 
 int /*<<< orphan*/  set_blkh_nr_item (struct block_head*,int) ; 

__attribute__((used)) static void leaf_delete_items_entirely(struct buffer_info *bi,
				       int first, int del_num)
{
	struct buffer_head *bh = bi->bi_bh;
	int nr;
	int i, j;
	int last_loc, last_removed_loc;
	struct block_head *blkh;
	struct item_head *ih;

	RFALSE(bh == NULL, "10210: buffer is 0");
	RFALSE(del_num < 0, "10215: del_num less than 0 (%d)", del_num);

	if (del_num == 0)
		return;

	blkh = B_BLK_HEAD(bh);
	nr = blkh_nr_item(blkh);

	RFALSE(first < 0 || first + del_num > nr,
	       "10220: first=%d, number=%d, there is %d items", first, del_num,
	       nr);

	if (first == 0 && del_num == nr) {
		/* this does not work */
		make_empty_node(bi);

		do_balance_mark_leaf_dirty(bi->tb, bh, 0);
		return;
	}

	ih = B_N_PITEM_HEAD(bh, first);

	/* location of unmovable item */
	j = (first == 0) ? bh->b_size : ih_location(ih - 1);

	/* delete items */
	last_loc = ih_location(&(ih[nr - 1 - first]));
	last_removed_loc = ih_location(&(ih[del_num - 1]));

	memmove(bh->b_data + last_loc + j - last_removed_loc,
		bh->b_data + last_loc, last_removed_loc - last_loc);

	/* delete item headers */
	memmove(ih, ih + del_num, (nr - first - del_num) * IH_SIZE);

	/* change item location */
	for (i = first; i < nr - del_num; i++)
		put_ih_location(&(ih[i - first]),
				ih_location(&(ih[i - first])) + (j -
								 last_removed_loc));

	/* sizes, item number */
	set_blkh_nr_item(blkh, blkh_nr_item(blkh) - del_num);
	set_blkh_free_space(blkh,
			    blkh_free_space(blkh) + (j - last_removed_loc +
						     IH_SIZE * del_num));

	do_balance_mark_leaf_dirty(bi->tb, bh, 0);

	if (bi->bi_parent) {
		struct disk_child *t_dc =
		    B_N_CHILD(bi->bi_parent, bi->bi_position);
		put_dc_size(t_dc,
			    dc_size(t_dc) - (j - last_removed_loc +
					     IH_SIZE * del_num));
		do_balance_mark_internal_dirty(bi->tb, bi->bi_parent, 0);
	}
}