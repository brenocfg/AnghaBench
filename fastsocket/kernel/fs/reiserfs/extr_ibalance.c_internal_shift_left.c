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
struct tree_balance {int dummy; } ;
struct buffer_info {scalar_t__ bi_position; int /*<<< orphan*/  bi_bh; int /*<<< orphan*/  bi_parent; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int B_NR_ITEMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIRST_TO_LAST ; 
 int /*<<< orphan*/  internal_define_dest_src_infos (int,struct tree_balance*,int,struct buffer_info*,struct buffer_info*,int*,struct buffer_head**) ; 
 int /*<<< orphan*/  internal_insert_key (struct buffer_info*,int,struct buffer_head*,int) ; 
 int /*<<< orphan*/  internal_move_pointers_items (struct buffer_info*,struct buffer_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_key (struct tree_balance*,struct buffer_head*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void internal_shift_left(int mode,	/* INTERNAL_FROM_S_TO_L | INTERNAL_FROM_R_TO_S */
				struct tree_balance *tb,
				int h, int pointer_amount)
{
	struct buffer_info dest_bi, src_bi;
	struct buffer_head *cf;
	int d_key_position;

	internal_define_dest_src_infos(mode, tb, h, &dest_bi, &src_bi,
				       &d_key_position, &cf);

	/*printk("pointer_amount = %d\n",pointer_amount); */

	if (pointer_amount) {
		/* insert delimiting key from common father of dest and src to node dest into position B_NR_ITEM(dest) */
		internal_insert_key(&dest_bi, B_NR_ITEMS(dest_bi.bi_bh), cf,
				    d_key_position);

		if (B_NR_ITEMS(src_bi.bi_bh) == pointer_amount - 1) {
			if (src_bi.bi_position /*src->b_item_order */  == 0)
				replace_key(tb, cf, d_key_position,
					    src_bi.
					    bi_parent /*src->b_parent */ , 0);
		} else
			replace_key(tb, cf, d_key_position, src_bi.bi_bh,
				    pointer_amount - 1);
	}
	/* last parameter is del_parameter */
	internal_move_pointers_items(&dest_bi, &src_bi, FIRST_TO_LAST,
				     pointer_amount, 0);

}