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
struct ext4_extent_header {int /*<<< orphan*/  eh_entries; } ;
struct ext4_extent {scalar_t__ ee_len; } ;

/* Variables and functions */
 struct ext4_extent* EXT_LAST_EXTENT (struct ext4_extent_header*) ; 
 int /*<<< orphan*/  ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (struct ext4_extent*,struct ext4_extent*,unsigned long) ; 

__attribute__((used)) static void
mext_insert_inside_block(struct ext4_extent *o_start,
			      struct ext4_extent *o_end,
			      struct ext4_extent *start_ext,
			      struct ext4_extent *new_ext,
			      struct ext4_extent *end_ext,
			      struct ext4_extent_header *eh,
			      int range_to_move)
{
	int i = 0;
	unsigned long len;

	/* Move the existing extents */
	if (range_to_move && o_end < EXT_LAST_EXTENT(eh)) {
		len = (unsigned long)(EXT_LAST_EXTENT(eh) + 1) -
			(unsigned long)(o_end + 1);
		memmove(o_end + 1 + range_to_move, o_end + 1, len);
	}

	/* Insert start entry */
	if (start_ext->ee_len)
		o_start[i++].ee_len = start_ext->ee_len;

	/* Insert new entry */
	if (new_ext->ee_len) {
		o_start[i] = *new_ext;
		ext4_ext_store_pblock(&o_start[i++], ext4_ext_pblock(new_ext));
	}

	/* Insert end entry */
	if (end_ext->ee_len)
		o_start[i] = *end_ext;

	/* Increment the total entries counter on the extent block */
	le16_add_cpu(&eh->eh_entries, range_to_move);
}