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
struct ext4_extent {void* ee_len; int /*<<< orphan*/  ee_block; } ;
typedef  int ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODATA ; 
 int /*<<< orphan*/  copy_extent_status (struct ext4_extent*,struct ext4_extent*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,int) ; 
 int le16_to_cpu (void*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mext_calc_swap_extents(struct ext4_extent *tmp_dext,
			      struct ext4_extent *tmp_oext,
			      ext4_lblk_t orig_off, ext4_lblk_t donor_off,
			      ext4_lblk_t max_count)
{
	ext4_lblk_t diff, orig_diff;
	struct ext4_extent dext_old, oext_old;

	BUG_ON(orig_off != donor_off);

	/* original and donor extents have to cover the same block offset */
	if (orig_off < le32_to_cpu(tmp_oext->ee_block) ||
	    le32_to_cpu(tmp_oext->ee_block) +
			ext4_ext_get_actual_len(tmp_oext) - 1 < orig_off)
		return -ENODATA;

	if (orig_off < le32_to_cpu(tmp_dext->ee_block) ||
	    le32_to_cpu(tmp_dext->ee_block) +
			ext4_ext_get_actual_len(tmp_dext) - 1 < orig_off)
		return -ENODATA;

	dext_old = *tmp_dext;
	oext_old = *tmp_oext;

	/* When tmp_dext is too large, pick up the target range. */
	diff = donor_off - le32_to_cpu(tmp_dext->ee_block);

	ext4_ext_store_pblock(tmp_dext, ext4_ext_pblock(tmp_dext) + diff);
	tmp_dext->ee_block =
			cpu_to_le32(le32_to_cpu(tmp_dext->ee_block) + diff);
	tmp_dext->ee_len = cpu_to_le16(le16_to_cpu(tmp_dext->ee_len) - diff);

	if (max_count < ext4_ext_get_actual_len(tmp_dext))
		tmp_dext->ee_len = cpu_to_le16(max_count);

	orig_diff = orig_off - le32_to_cpu(tmp_oext->ee_block);
	ext4_ext_store_pblock(tmp_oext, ext4_ext_pblock(tmp_oext) + orig_diff);

	/* Adjust extent length if donor extent is larger than orig */
	if (ext4_ext_get_actual_len(tmp_dext) >
	    ext4_ext_get_actual_len(tmp_oext) - orig_diff)
		tmp_dext->ee_len = cpu_to_le16(le16_to_cpu(tmp_oext->ee_len) -
						orig_diff);

	tmp_oext->ee_len = cpu_to_le16(ext4_ext_get_actual_len(tmp_dext));

	copy_extent_status(&oext_old, tmp_dext);
	copy_extent_status(&dext_old, tmp_oext);

	return 0;
}