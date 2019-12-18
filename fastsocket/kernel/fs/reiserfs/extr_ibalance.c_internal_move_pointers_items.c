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
struct buffer_info {int /*<<< orphan*/  bi_bh; } ;

/* Variables and functions */
 int B_NR_ITEMS (int /*<<< orphan*/ ) ; 
 int FIRST_TO_LAST ; 
 int /*<<< orphan*/  internal_copy_pointers_items (struct buffer_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  internal_delete_pointers_items (struct buffer_info*,int,int,int) ; 

__attribute__((used)) static void internal_move_pointers_items(struct buffer_info *dest_bi,
					 struct buffer_info *src_bi,
					 int last_first, int cpy_num,
					 int del_par)
{
	int first_pointer;
	int first_item;

	internal_copy_pointers_items(dest_bi, src_bi->bi_bh, last_first,
				     cpy_num);

	if (last_first == FIRST_TO_LAST) {	/* shift_left occurs */
		first_pointer = 0;
		first_item = 0;
		/* delete cpy_num - del_par pointers and keys starting for pointers with first_pointer,
		   for key - with first_item */
		internal_delete_pointers_items(src_bi, first_pointer,
					       first_item, cpy_num - del_par);
	} else {		/* shift_right occurs */
		int i, j;

		i = (cpy_num - del_par ==
		     (j =
		      B_NR_ITEMS(src_bi->bi_bh)) + 1) ? 0 : j - cpy_num +
		    del_par;

		internal_delete_pointers_items(src_bi,
					       j + 1 - cpy_num + del_par, i,
					       cpy_num - del_par);
	}
}