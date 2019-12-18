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
struct list_blocks_struct {int /*<<< orphan*/  first_pblock; scalar_t__ first_block; scalar_t__ last_block; } ;
struct inode {int dummy; } ;
struct ext4_extent {int /*<<< orphan*/  ee_len; int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_RESERVE_TRANS_BLOCKS ; 
 scalar_t__ IS_ERR (struct ext4_ext_path*) ; 
 int PTR_ERR (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int ext4_ext_calc_credits_for_single_extent (struct inode*,scalar_t__,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 struct ext4_ext_path* ext4_ext_find_extent (struct inode*,scalar_t__,int /*<<< orphan*/ *) ; 
 int ext4_ext_insert_extent (int /*<<< orphan*/ *,struct inode*,struct ext4_ext_path*,struct ext4_extent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_store_pblock (struct ext4_extent*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_handle_has_enough_credits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ext4_journal_extend (int /*<<< orphan*/ *,int) ; 
 int ext4_journal_restart (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 

__attribute__((used)) static int finish_range(handle_t *handle, struct inode *inode,
				struct list_blocks_struct *lb)

{
	int retval = 0, needed;
	struct ext4_extent newext;
	struct ext4_ext_path *path;
	if (lb->first_pblock == 0)
		return 0;

	/* Add the extent to temp inode*/
	newext.ee_block = cpu_to_le32(lb->first_block);
	newext.ee_len   = cpu_to_le16(lb->last_block - lb->first_block + 1);
	ext4_ext_store_pblock(&newext, lb->first_pblock);
	path = ext4_ext_find_extent(inode, lb->first_block, NULL);

	if (IS_ERR(path)) {
		retval = PTR_ERR(path);
		path = NULL;
		goto err_out;
	}

	/*
	 * Calculate the credit needed to inserting this extent
	 * Since we are doing this in loop we may accumalate extra
	 * credit. But below we try to not accumalate too much
	 * of them by restarting the journal.
	 */
	needed = ext4_ext_calc_credits_for_single_extent(inode,
		    lb->last_block - lb->first_block + 1, path);

	/*
	 * Make sure the credit we accumalated is not really high
	 */
	if (needed && ext4_handle_has_enough_credits(handle,
						EXT4_RESERVE_TRANS_BLOCKS)) {
		retval = ext4_journal_restart(handle, needed);
		if (retval)
			goto err_out;
	} else if (needed) {
		retval = ext4_journal_extend(handle, needed);
		if (retval) {
			/*
			 * IF not able to extend the journal restart the journal
			 */
			retval = ext4_journal_restart(handle, needed);
			if (retval)
				goto err_out;
		}
	}
	retval = ext4_ext_insert_extent(handle, inode, path, &newext, 0);
err_out:
	if (path) {
		ext4_ext_drop_refs(path);
		kfree(path);
	}
	lb->first_pblock = 0;
	return retval;
}