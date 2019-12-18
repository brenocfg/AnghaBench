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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct ext4_extent {void* ee_block; void* ee_len; } ;
struct ext4_ext_path {int /*<<< orphan*/  p_hdr; struct ext4_extent* p_ext; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  int ext4_lblk_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 int EIO ; 
 struct ext4_extent* EXT_FIRST_EXTENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_extent_status (struct ext4_extent*,struct ext4_extent*) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 scalar_t__ ext4_can_extents_be_merged (struct inode*,struct ext4_extent*,struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 scalar_t__ ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,scalar_t__) ; 
 int ext_depth (struct inode*) ; 
 int le32_to_cpu (void*) ; 
 int mext_insert_extents (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,struct ext4_extent*,struct ext4_extent*,struct ext4_extent*,struct ext4_extent*,struct ext4_extent*) ; 

__attribute__((used)) static int
mext_leaf_block(handle_t *handle, struct inode *orig_inode,
		     struct ext4_ext_path *orig_path, struct ext4_extent *dext,
		     ext4_lblk_t *from)
{
	struct ext4_extent *oext, *o_start, *o_end, *prev_ext;
	struct ext4_extent new_ext, start_ext, end_ext;
	ext4_lblk_t new_ext_end;
	ext4_fsblk_t new_phys_end;
	int oext_alen, new_ext_alen, end_ext_alen;
	int depth = ext_depth(orig_inode);
	int ret;

	o_start = o_end = oext = orig_path[depth].p_ext;
	oext_alen = ext4_ext_get_actual_len(oext);
	start_ext.ee_len = end_ext.ee_len = 0;

	new_ext.ee_block = cpu_to_le32(*from);
	ext4_ext_store_pblock(&new_ext, ext4_ext_pblock(dext));
	new_ext.ee_len = dext->ee_len;
	new_ext_alen = ext4_ext_get_actual_len(&new_ext);
	new_ext_end = le32_to_cpu(new_ext.ee_block) + new_ext_alen - 1;
	new_phys_end = ext4_ext_pblock(&new_ext) + new_ext_alen - 1;

	/*
	 * Case: original extent is first
	 * oext      |--------|
	 * new_ext      |--|
	 * start_ext |--|
	 */
	if (le32_to_cpu(oext->ee_block) < le32_to_cpu(new_ext.ee_block) &&
		le32_to_cpu(new_ext.ee_block) <
		le32_to_cpu(oext->ee_block) + oext_alen) {
		start_ext.ee_len = cpu_to_le16(le32_to_cpu(new_ext.ee_block) -
					       le32_to_cpu(oext->ee_block));
		copy_extent_status(oext, &start_ext);
	} else if (oext > EXT_FIRST_EXTENT(orig_path[depth].p_hdr)) {
		prev_ext = oext - 1;
		/*
		 * We can merge new_ext into previous extent,
		 * if these are contiguous and same extent type.
		 */
		if (ext4_can_extents_be_merged(orig_inode, prev_ext,
					       &new_ext)) {
			o_start = prev_ext;
			start_ext.ee_len = cpu_to_le16(
				ext4_ext_get_actual_len(prev_ext) +
				new_ext_alen);
			copy_extent_status(prev_ext, &start_ext);
			new_ext.ee_len = 0;
		}
	}

	/*
	 * Case: new_ext_end must be less than oext
	 * oext      |-----------|
	 * new_ext       |-------|
	 */
	if (le32_to_cpu(oext->ee_block) + oext_alen - 1 < new_ext_end) {
		ext4_error(orig_inode->i_sb,
			"new_ext_end(%u) should be less than or equal to "
			"oext->ee_block(%u) + oext_alen(%d) - 1",
			new_ext_end, le32_to_cpu(oext->ee_block),
			oext_alen);
		ret = -EIO;
		goto out;
	}

	/*
	 * Case: new_ext is smaller than original extent
	 * oext    |---------------|
	 * new_ext |-----------|
	 * end_ext             |---|
	 */
	if (le32_to_cpu(oext->ee_block) <= new_ext_end &&
		new_ext_end < le32_to_cpu(oext->ee_block) + oext_alen - 1) {
		end_ext.ee_len =
			cpu_to_le16(le32_to_cpu(oext->ee_block) +
			oext_alen - 1 - new_ext_end);
		copy_extent_status(oext, &end_ext);
		end_ext_alen = ext4_ext_get_actual_len(&end_ext);
		ext4_ext_store_pblock(&end_ext,
			(ext4_ext_pblock(o_end) + oext_alen - end_ext_alen));
		end_ext.ee_block =
			cpu_to_le32(le32_to_cpu(o_end->ee_block) +
			oext_alen - end_ext_alen);
	}

	ret = mext_insert_extents(handle, orig_inode, orig_path, o_start,
				o_end, &start_ext, &new_ext, &end_ext);
out:
	return ret;
}