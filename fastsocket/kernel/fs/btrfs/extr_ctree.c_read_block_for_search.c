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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {scalar_t__ reada; } ;
struct btrfs_key {int /*<<< orphan*/  objectid; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 scalar_t__ btrfs_buffer_uptodate (struct extent_buffer*,int /*<<< orphan*/ ,int) ; 
 struct extent_buffer* btrfs_find_tree_block (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_level_size (struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_node_blockptr (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_node_ptr_generation (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_set_path_blocking (struct btrfs_path*) ; 
 int /*<<< orphan*/  btrfs_unlock_up_safe (struct btrfs_path*,int) ; 
 int /*<<< orphan*/  free_extent_buffer (struct extent_buffer*) ; 
 struct extent_buffer* read_tree_block (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reada_for_search (struct btrfs_root*,struct btrfs_path*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_block_for_search(struct btrfs_trans_handle *trans,
		       struct btrfs_root *root, struct btrfs_path *p,
		       struct extent_buffer **eb_ret, int level, int slot,
		       struct btrfs_key *key, u64 time_seq)
{
	u64 blocknr;
	u64 gen;
	u32 blocksize;
	struct extent_buffer *b = *eb_ret;
	struct extent_buffer *tmp;
	int ret;

	blocknr = btrfs_node_blockptr(b, slot);
	gen = btrfs_node_ptr_generation(b, slot);
	blocksize = btrfs_level_size(root, level - 1);

	tmp = btrfs_find_tree_block(root, blocknr, blocksize);
	if (tmp) {
		/* first we do an atomic uptodate check */
		if (btrfs_buffer_uptodate(tmp, 0, 1) > 0) {
			if (btrfs_buffer_uptodate(tmp, gen, 1) > 0) {
				/*
				 * we found an up to date block without
				 * sleeping, return
				 * right away
				 */
				*eb_ret = tmp;
				return 0;
			}
			/* the pages were up to date, but we failed
			 * the generation number check.  Do a full
			 * read for the generation number that is correct.
			 * We must do this without dropping locks so
			 * we can trust our generation number
			 */
			free_extent_buffer(tmp);
			btrfs_set_path_blocking(p);

			/* now we're allowed to do a blocking uptodate check */
			tmp = read_tree_block(root, blocknr, blocksize, gen);
			if (tmp && btrfs_buffer_uptodate(tmp, gen, 0) > 0) {
				*eb_ret = tmp;
				return 0;
			}
			free_extent_buffer(tmp);
			btrfs_release_path(p);
			return -EIO;
		}
	}

	/*
	 * reduce lock contention at high levels
	 * of the btree by dropping locks before
	 * we read.  Don't release the lock on the current
	 * level because we need to walk this node to figure
	 * out which blocks to read.
	 */
	btrfs_unlock_up_safe(p, level + 1);
	btrfs_set_path_blocking(p);

	free_extent_buffer(tmp);
	if (p->reada)
		reada_for_search(root, p, level, slot, key->objectid);

	btrfs_release_path(p);

	ret = -EAGAIN;
	tmp = read_tree_block(root, blocknr, blocksize, 0);
	if (tmp) {
		/*
		 * If the read above didn't mark this buffer up to date,
		 * it will never end up being up to date.  Set ret to EIO now
		 * and give up so that our caller doesn't loop forever
		 * on our EAGAINs.
		 */
		if (!btrfs_buffer_uptodate(tmp, 0, 0))
			ret = -EIO;
		free_extent_buffer(tmp);
	}
	return ret;
}