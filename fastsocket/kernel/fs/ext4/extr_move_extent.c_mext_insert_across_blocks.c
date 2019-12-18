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
struct inode {int dummy; } ;
struct ext4_extent {scalar_t__ ee_block; scalar_t__ ee_len; } ;
struct ext4_ext_path {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ext4_debug (char*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 scalar_t__ ext4_ext_insert_extent (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,struct ext4_extent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_pblock (struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,int /*<<< orphan*/ ) ; 
 int get_ext_path (struct inode*,scalar_t__,struct ext4_ext_path**) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 scalar_t__ le32_to_cpu (scalar_t__) ; 

__attribute__((used)) static int
mext_insert_across_blocks(handle_t *handle, struct inode *orig_inode,
		struct ext4_extent *o_start, struct ext4_extent *o_end,
		struct ext4_extent *start_ext, struct ext4_extent *new_ext,
		struct ext4_extent *end_ext)
{
	struct ext4_ext_path *orig_path = NULL;
	ext4_lblk_t eblock = 0;
	int new_flag = 0;
	int end_flag = 0;
	int err = 0;

	if (start_ext->ee_len && new_ext->ee_len && end_ext->ee_len) {
		if (o_start == o_end) {

			/*       start_ext   new_ext    end_ext
			 * donor |---------|-----------|--------|
			 * orig  |------------------------------|
			 */
			end_flag = 1;
		} else {

			/*       start_ext   new_ext   end_ext
			 * donor |---------|----------|---------|
			 * orig  |---------------|--------------|
			 */
			o_end->ee_block = end_ext->ee_block;
			o_end->ee_len = end_ext->ee_len;
			ext4_ext_store_pblock(o_end, ext4_ext_pblock(end_ext));
		}

		o_start->ee_len = start_ext->ee_len;
		new_flag = 1;

	} else if (start_ext->ee_len && new_ext->ee_len &&
		   !end_ext->ee_len && o_start == o_end) {

		/*	 start_ext	new_ext
		 * donor |--------------|---------------|
		 * orig  |------------------------------|
		 */
		o_start->ee_len = start_ext->ee_len;
		new_flag = 1;

	} else if (!start_ext->ee_len && new_ext->ee_len &&
		   end_ext->ee_len && o_start == o_end) {

		/*	  new_ext	end_ext
		 * donor |--------------|---------------|
		 * orig  |------------------------------|
		 */
		o_end->ee_block = end_ext->ee_block;
		o_end->ee_len = end_ext->ee_len;
		ext4_ext_store_pblock(o_end, ext4_ext_pblock(end_ext));

		/*
		 * Set 0 to the extent block if new_ext was
		 * the first block.
		 */
		if (new_ext->ee_block)
			eblock = le32_to_cpu(new_ext->ee_block);

		new_flag = 1;
	} else {
		ext4_debug("ext4 move extent: Unexpected insert case\n");
		return -EIO;
	}

	if (new_flag) {
		err = get_ext_path(orig_inode, eblock, &orig_path);
		if (err)
			goto out;

		if (ext4_ext_insert_extent(handle, orig_inode,
					orig_path, new_ext, 0))
			goto out;
	}

	if (end_flag) {
		err = get_ext_path(orig_inode,
				le32_to_cpu(end_ext->ee_block) - 1, &orig_path);
		if (err)
			goto out;

		if (ext4_ext_insert_extent(handle, orig_inode,
					   orig_path, end_ext, 0))
			goto out;
	}
out:
	if (orig_path) {
		ext4_ext_drop_refs(orig_path);
		kfree(orig_path);
	}

	return err;

}