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
struct item_head {int /*<<< orphan*/  ih_version; int /*<<< orphan*/  ih_key; } ;
struct buffer_info {struct buffer_head* bi_bh; } ;
struct buffer_head {int b_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_NR_ITEMS (struct buffer_head*) ; 
 scalar_t__ B_N_PITEM (struct buffer_head*,int) ; 
 struct item_head* B_N_PITEM_HEAD (struct buffer_head*,int) ; 
 int FIRST_TO_LAST ; 
 int /*<<< orphan*/  IH_SIZE ; 
 scalar_t__ I_ENTRY_COUNT (struct item_head*) ; 
 int LAST_TO_FIRST ; 
 scalar_t__ MAX_US_INT ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int /*<<< orphan*/  SHORT_KEY_SIZE ; 
 int /*<<< orphan*/  TYPE_DIRECT ; 
 int /*<<< orphan*/  TYPE_INDIRECT ; 
 int UNFM_P_SIZE ; 
 scalar_t__ get_ih_free_space (struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 scalar_t__ is_direct_le_ih (struct item_head*) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ is_indirect_le_ih (struct item_head*) ; 
 scalar_t__ le_ih_k_offset (struct item_head*) ; 
 int /*<<< orphan*/  leaf_copy_dir_entries (struct buffer_info*,struct buffer_head*,int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  leaf_insert_into_buf (struct buffer_info*,int /*<<< orphan*/ ,struct item_head*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct item_head*,struct item_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  op_is_left_mergeable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_ih_item_len (struct item_head*,int) ; 
 int /*<<< orphan*/  set_ih_free_space (struct item_head*,scalar_t__) ; 
 int /*<<< orphan*/  set_le_ih_k_offset (struct item_head*,scalar_t__) ; 
 int /*<<< orphan*/  set_le_ih_k_type (struct item_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void leaf_item_bottle(struct buffer_info *dest_bi,
			     struct buffer_head *src, int last_first,
			     int item_num, int cpy_bytes)
{
	struct buffer_head *dest = dest_bi->bi_bh;
	struct item_head *ih;

	RFALSE(cpy_bytes == -1,
	       "vs-10170: bytes == - 1 means: do not split item");

	if (last_first == FIRST_TO_LAST) {
		/* if ( if item in position item_num in buffer SOURCE is directory item ) */
		ih = B_N_PITEM_HEAD(src, item_num);
		if (is_direntry_le_ih(ih))
			leaf_copy_dir_entries(dest_bi, src, FIRST_TO_LAST,
					      item_num, 0, cpy_bytes);
		else {
			struct item_head n_ih;

			/* copy part of the body of the item number 'item_num' of SOURCE to the end of the DEST
			   part defined by 'cpy_bytes'; create new item header; change old item_header (????);
			   n_ih = new item_header;
			 */
			memcpy(&n_ih, ih, IH_SIZE);
			put_ih_item_len(&n_ih, cpy_bytes);
			if (is_indirect_le_ih(ih)) {
				RFALSE(cpy_bytes == ih_item_len(ih)
				       && get_ih_free_space(ih),
				       "vs-10180: when whole indirect item is bottle to left neighbor, it must have free_space==0 (not %lu)",
				       (long unsigned)get_ih_free_space(ih));
				set_ih_free_space(&n_ih, 0);
			}

			RFALSE(op_is_left_mergeable(&(ih->ih_key), src->b_size),
			       "vs-10190: bad mergeability of item %h", ih);
			n_ih.ih_version = ih->ih_version;	/* JDM Endian safe, both le */
			leaf_insert_into_buf(dest_bi, B_NR_ITEMS(dest), &n_ih,
					     B_N_PITEM(src, item_num), 0);
		}
	} else {
		/*  if ( if item in position item_num in buffer SOURCE is directory item ) */
		ih = B_N_PITEM_HEAD(src, item_num);
		if (is_direntry_le_ih(ih))
			leaf_copy_dir_entries(dest_bi, src, LAST_TO_FIRST,
					      item_num,
					      I_ENTRY_COUNT(ih) - cpy_bytes,
					      cpy_bytes);
		else {
			struct item_head n_ih;

			/* copy part of the body of the item number 'item_num' of SOURCE to the begin of the DEST
			   part defined by 'cpy_bytes'; create new item header;
			   n_ih = new item_header;
			 */
			memcpy(&n_ih, ih, SHORT_KEY_SIZE);

			n_ih.ih_version = ih->ih_version;	/* JDM Endian safe, both le */

			if (is_direct_le_ih(ih)) {
				set_le_ih_k_offset(&n_ih,
						   le_ih_k_offset(ih) +
						   ih_item_len(ih) - cpy_bytes);
				set_le_ih_k_type(&n_ih, TYPE_DIRECT);
				set_ih_free_space(&n_ih, MAX_US_INT);
			} else {
				/* indirect item */
				RFALSE(!cpy_bytes && get_ih_free_space(ih),
				       "vs-10200: ih->ih_free_space must be 0 when indirect item will be appended");
				set_le_ih_k_offset(&n_ih,
						   le_ih_k_offset(ih) +
						   (ih_item_len(ih) -
						    cpy_bytes) / UNFM_P_SIZE *
						   dest->b_size);
				set_le_ih_k_type(&n_ih, TYPE_INDIRECT);
				set_ih_free_space(&n_ih, get_ih_free_space(ih));
			}

			/* set item length */
			put_ih_item_len(&n_ih, cpy_bytes);

			n_ih.ih_version = ih->ih_version;	/* JDM Endian safe, both le */

			leaf_insert_into_buf(dest_bi, 0, &n_ih,
					     B_N_PITEM(src,
						       item_num) +
					     ih_item_len(ih) - cpy_bytes, 0);
		}
	}
}