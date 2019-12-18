#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int i_blkbits; scalar_t__ i_ino; int /*<<< orphan*/  i_sb; } ;
struct file {TYPE_1__* f_dentry; } ;
struct ext4_extent {int /*<<< orphan*/  ee_block; } ;
struct ext4_ext_path {int p_depth; struct ext4_extent* p_ext; } ;
typedef  int pgoff_t ;
typedef  int ext4_lblk_t ;
typedef  int __u64 ;
struct TYPE_2__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  double_down_write_data_sem (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  double_up_write_data_sem (struct inode*,struct inode*) ; 
 scalar_t__ ext4_can_extents_be_merged (struct inode*,struct ext4_extent*,struct ext4_extent*) ; 
 int /*<<< orphan*/  ext4_debug (char*,...) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int /*<<< orphan*/  ext4_error (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int ext4_ext_get_actual_len (struct ext4_extent*) ; 
 int ext4_ext_is_uninitialized (struct ext4_extent*) ; 
 int ext_depth (struct inode*) ; 
 int get_ext_path (struct inode*,int,struct ext4_ext_path**) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int mext_check_arguments (struct inode*,struct inode*,int,int,int*) ; 
 int mext_inode_double_lock (struct inode*,struct inode*) ; 
 int mext_inode_double_unlock (struct inode*,struct inode*) ; 
 int mext_next_extent (struct inode*,struct ext4_ext_path*,struct ext4_extent**) ; 
 int min (int,int) ; 
 int move_extent_per_page (struct file*,struct inode*,int,int,int,int,int*) ; 

int
ext4_move_extents(struct file *o_filp, struct file *d_filp,
		 __u64 orig_start, __u64 donor_start, __u64 len,
		 __u64 *moved_len)
{
	struct inode *orig_inode = o_filp->f_dentry->d_inode;
	struct inode *donor_inode = d_filp->f_dentry->d_inode;
	struct ext4_ext_path *orig_path = NULL, *holecheck_path = NULL;
	struct ext4_extent *ext_prev, *ext_cur, *ext_dummy;
	ext4_lblk_t block_start = orig_start;
	ext4_lblk_t block_end, seq_start, add_blocks, file_end, seq_blocks = 0;
	ext4_lblk_t rest_blocks;
	pgoff_t orig_page_offset = 0, seq_end_page;
	int ret1, ret2, depth, last_extent = 0;
	int blocks_per_page = PAGE_CACHE_SIZE >> orig_inode->i_blkbits;
	int data_offset_in_page;
	int block_len_in_page;
	int uninit;

	/* orig and donor should be different file */
	if (orig_inode->i_ino == donor_inode->i_ino) {
		ext4_debug("ext4 move extent: The argument files should not "
			"be same file [ino:orig %lu, donor %lu]\n",
			orig_inode->i_ino, donor_inode->i_ino);
		return -EINVAL;
	}

	/* Protect orig and donor inodes against a truncate */
	ret1 = mext_inode_double_lock(orig_inode, donor_inode);
	if (ret1 < 0)
		return ret1;

	/* Protect extent tree against block allocations via delalloc */
	double_down_write_data_sem(orig_inode, donor_inode);
	/* Check the filesystem environment whether move_extent can be done */
	ret1 = mext_check_arguments(orig_inode, donor_inode, orig_start,
				    donor_start, &len);
	if (ret1)
		goto out;

	file_end = (i_size_read(orig_inode) - 1) >> orig_inode->i_blkbits;
	block_end = block_start + len - 1;
	if (file_end < block_end)
		len -= block_end - file_end;

	ret1 = get_ext_path(orig_inode, block_start, &orig_path);
	if (ret1)
		goto out;

	/* Get path structure to check the hole */
	ret1 = get_ext_path(orig_inode, block_start, &holecheck_path);
	if (ret1)
		goto out;

	depth = ext_depth(orig_inode);
	ext_cur = holecheck_path[depth].p_ext;

	/*
	 * Get proper starting location of block replacement if block_start was
	 * within the hole.
	 */
	if (le32_to_cpu(ext_cur->ee_block) +
		ext4_ext_get_actual_len(ext_cur) - 1 < block_start) {
		/*
		 * The hole exists between extents or the tail of
		 * original file.
		 */
		last_extent = mext_next_extent(orig_inode,
					holecheck_path, &ext_cur);
		if (last_extent < 0) {
			ret1 = last_extent;
			goto out;
		}
		last_extent = mext_next_extent(orig_inode, orig_path,
							&ext_dummy);
		if (last_extent < 0) {
			ret1 = last_extent;
			goto out;
		}
		seq_start = le32_to_cpu(ext_cur->ee_block);
	} else if (le32_to_cpu(ext_cur->ee_block) > block_start)
		/* The hole exists at the beginning of original file. */
		seq_start = le32_to_cpu(ext_cur->ee_block);
	else
		seq_start = block_start;

	/* No blocks within the specified range. */
	if (le32_to_cpu(ext_cur->ee_block) > block_end) {
		ext4_debug("ext4 move extent: The specified range of file "
							"may be the hole\n");
		ret1 = -EINVAL;
		goto out;
	}

	/* Adjust start blocks */
	add_blocks = min(le32_to_cpu(ext_cur->ee_block) +
			 ext4_ext_get_actual_len(ext_cur), block_end + 1) -
		     max(le32_to_cpu(ext_cur->ee_block), block_start);

	while (!last_extent && le32_to_cpu(ext_cur->ee_block) <= block_end) {
		seq_blocks += add_blocks;

		/* Adjust tail blocks */
		if (seq_start + seq_blocks - 1 > block_end)
			seq_blocks = block_end - seq_start + 1;

		ext_prev = ext_cur;
		last_extent = mext_next_extent(orig_inode, holecheck_path,
						&ext_cur);
		if (last_extent < 0) {
			ret1 = last_extent;
			break;
		}
		add_blocks = ext4_ext_get_actual_len(ext_cur);

		/*
		 * Extend the length of contiguous block (seq_blocks)
		 * if extents are contiguous.
		 */
		if (ext4_can_extents_be_merged(orig_inode,
					       ext_prev, ext_cur) &&
		    block_end >= le32_to_cpu(ext_cur->ee_block) &&
		    !last_extent)
			continue;

		/* Is original extent is uninitialized */
		uninit = ext4_ext_is_uninitialized(ext_prev);

		data_offset_in_page = seq_start % blocks_per_page;

		/*
		 * Calculate data blocks count that should be swapped
		 * at the first page.
		 */
		if (data_offset_in_page + seq_blocks > blocks_per_page) {
			/* Swapped blocks are across pages */
			block_len_in_page =
					blocks_per_page - data_offset_in_page;
		} else {
			/* Swapped blocks are in a page */
			block_len_in_page = seq_blocks;
		}

		orig_page_offset = seq_start >>
				(PAGE_CACHE_SHIFT - orig_inode->i_blkbits);
		seq_end_page = (seq_start + seq_blocks - 1) >>
				(PAGE_CACHE_SHIFT - orig_inode->i_blkbits);
		seq_start = le32_to_cpu(ext_cur->ee_block);
		rest_blocks = seq_blocks;

		/*
		 * Up semaphore to avoid following problems:
		 * a. transaction deadlock among ext4_journal_start,
		 *    ->write_begin via pagefault, and jbd2_journal_commit
		 * b. racing with ->readpage, ->write_begin, and ext4_get_block
		 *    in move_extent_per_page
		 */
		double_up_write_data_sem(orig_inode, donor_inode);

		while (orig_page_offset <= seq_end_page) {

			/* Swap original branches with new branches */
			block_len_in_page = move_extent_per_page(
						o_filp, donor_inode,
						orig_page_offset,
						data_offset_in_page,
						block_len_in_page, uninit,
						&ret1);

			/* Count how many blocks we have exchanged */
			*moved_len += block_len_in_page;
			if (ret1 < 0)
				break;
			if (*moved_len > len) {
				ext4_error(orig_inode->i_sb,
					"We replaced blocks too much! "
					"sum of replaced: %llu requested: %llu",
					*moved_len, len);
				ret1 = -EIO;
				break;
			}

			orig_page_offset++;
			data_offset_in_page = 0;
			rest_blocks -= block_len_in_page;
			if (rest_blocks > blocks_per_page)
				block_len_in_page = blocks_per_page;
			else
				block_len_in_page = rest_blocks;
		}

		double_down_write_data_sem(orig_inode, donor_inode);
		if (ret1 < 0)
			break;

		/* Decrease buffer counter */
		if (holecheck_path)
			ext4_ext_drop_refs(holecheck_path);
		ret1 = get_ext_path(orig_inode, seq_start, &holecheck_path);
		if (ret1)
			break;
		depth = holecheck_path->p_depth;

		/* Decrease buffer counter */
		if (orig_path)
			ext4_ext_drop_refs(orig_path);
		ret1 = get_ext_path(orig_inode, seq_start, &orig_path);
		if (ret1)
			break;

		ext_cur = holecheck_path[depth].p_ext;
		add_blocks = ext4_ext_get_actual_len(ext_cur);
		seq_blocks = 0;

	}
out:
	if (*moved_len) {
		ext4_discard_preallocations(orig_inode);
		ext4_discard_preallocations(donor_inode);
	}

	if (orig_path) {
		ext4_ext_drop_refs(orig_path);
		kfree(orig_path);
	}
	if (holecheck_path) {
		ext4_ext_drop_refs(holecheck_path);
		kfree(holecheck_path);
	}
	double_up_write_data_sem(orig_inode, donor_inode);
	ret2 = mext_inode_double_unlock(orig_inode, donor_inode);

	if (ret1)
		return ret1;
	else if (ret2)
		return ret2;

	return 0;
}