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
struct ext4_extent_header {int /*<<< orphan*/  eh_max; int /*<<< orphan*/  eh_entries; } ;
struct ext4_ext_path {short p_depth; int /*<<< orphan*/ * p_ext; int /*<<< orphan*/  p_block; int /*<<< orphan*/ * p_idx; struct ext4_extent_header* p_hdr; struct buffer_head* p_bh; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ext4_ext_path* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT4_ERROR_INODE (struct inode*,char*,short,short) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ bh_submit_read (struct buffer_head*) ; 
 int /*<<< orphan*/  bh_uptodate_or_lock (struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_ext_binsearch (struct inode*,struct ext4_ext_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_ext_binsearch_idx (struct inode*,struct ext4_ext_path*,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_ext_check_block (struct inode*,struct ext4_extent_header*,short,struct buffer_head*) ; 
 int /*<<< orphan*/  ext4_ext_drop_refs (struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_ext_pblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_ext_show_path (struct inode*,struct ext4_ext_path*) ; 
 int /*<<< orphan*/  ext4_idx_pblock (int /*<<< orphan*/ *) ; 
 struct ext4_extent_header* ext_block_hdr (struct buffer_head*) ; 
 int /*<<< orphan*/  ext_debug (char*,short,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 short ext_depth (struct inode*) ; 
 struct ext4_extent_header* ext_inode_hdr (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ext4_ext_path*) ; 
 struct ext4_ext_path* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bh (struct buffer_head*) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

struct ext4_ext_path *
ext4_ext_find_extent(struct inode *inode, ext4_lblk_t block,
					struct ext4_ext_path *path)
{
	struct ext4_extent_header *eh;
	struct buffer_head *bh;
	short int depth, i, ppos = 0, alloc = 0;

	eh = ext_inode_hdr(inode);
	depth = ext_depth(inode);

	/* account possible depth increase */
	if (!path) {
		path = kzalloc(sizeof(struct ext4_ext_path) * (depth + 2),
				GFP_NOFS);
		if (!path)
			return ERR_PTR(-ENOMEM);
		alloc = 1;
	}
	path[0].p_hdr = eh;
	path[0].p_bh = NULL;

	i = depth;
	/* walk through the tree */
	while (i) {
		ext_debug("depth %d: num %d, max %d\n",
			  ppos, le16_to_cpu(eh->eh_entries), le16_to_cpu(eh->eh_max));

		ext4_ext_binsearch_idx(inode, path + ppos, block);
		path[ppos].p_block = ext4_idx_pblock(path[ppos].p_idx);
		path[ppos].p_depth = i;
		path[ppos].p_ext = NULL;

		bh = sb_getblk(inode->i_sb, path[ppos].p_block);
		if (unlikely(!bh))
			goto err;
		if (!bh_uptodate_or_lock(bh)) {
			if (bh_submit_read(bh) < 0) {
				put_bh(bh);
				goto err;
			}
		}
		eh = ext_block_hdr(bh);
		ppos++;
		if (unlikely(ppos > depth)) {
			put_bh(bh);
			EXT4_ERROR_INODE(inode,
					 "ppos %d > depth %d", ppos, depth);
			goto err;
		}
		path[ppos].p_bh = bh;
		path[ppos].p_hdr = eh;
		i--;

		if (ext4_ext_check_block(inode, eh, i, bh))
			goto err;
	}

	path[ppos].p_depth = i;
	path[ppos].p_ext = NULL;
	path[ppos].p_idx = NULL;

	/* find extent */
	ext4_ext_binsearch(inode, path + ppos, block);
	/* if not an empty leaf */
	if (path[ppos].p_ext)
		path[ppos].p_block = ext4_ext_pblock(path[ppos].p_ext);

	ext4_ext_show_path(inode, path);

	return path;

err:
	ext4_ext_drop_refs(path);
	if (alloc)
		kfree(path);
	return ERR_PTR(-EIO);
}