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
struct super_block {int s_blocksize_bits; } ;
struct page {int index; TYPE_1__* mapping; } ;
struct inode {int i_blkbits; struct super_block* i_sb; } ;
struct ext4_group_info {char* bb_counters; scalar_t__ bb_fragments; } ;
struct ext4_group_desc {int bg_flags; } ;
struct buffer_head {char* b_data; int /*<<< orphan*/  b_end_io; } ;
typedef  int ext4_group_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXT4_BG_BLOCK_UNINIT ; 
 int /*<<< orphan*/  EXT4_MB_GRP_NEED_INIT (struct ext4_group_info*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_CACHE_SIZE ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 scalar_t__ bitmap_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  ext4_block_bitmap (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 struct ext4_group_info* ext4_get_group_info (struct super_block*,int) ; 
 int ext4_get_groups_count (struct super_block*) ; 
 int /*<<< orphan*/  ext4_init_block_bitmap (struct super_block*,struct buffer_head*,int,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,int) ; 
 int /*<<< orphan*/  ext4_mb_generate_buddy (struct super_block*,char*,char*,int) ; 
 int /*<<< orphan*/  ext4_mb_generate_from_freelist (struct super_block*,char*,int) ; 
 int /*<<< orphan*/  ext4_mb_generate_from_pa (struct super_block*,char*,int) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,int) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  kfree (struct buffer_head**) ; 
 struct buffer_head** kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mb_debug (int,char*,int,...) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 char* page_address (struct page*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bitmap_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static int ext4_mb_init_cache(struct page *page, char *incore)
{
	ext4_group_t ngroups;
	int blocksize;
	int blocks_per_page;
	int groups_per_page;
	int err = 0;
	int i;
	ext4_group_t first_group;
	int first_block;
	struct super_block *sb;
	struct buffer_head *bhs;
	struct buffer_head **bh;
	struct inode *inode;
	char *data;
	char *bitmap;
	struct ext4_group_info *grinfo;

	mb_debug(1, "init page %lu\n", page->index);

	inode = page->mapping->host;
	sb = inode->i_sb;
	ngroups = ext4_get_groups_count(sb);
	blocksize = 1 << inode->i_blkbits;
	blocks_per_page = PAGE_CACHE_SIZE / blocksize;

	groups_per_page = blocks_per_page >> 1;
	if (groups_per_page == 0)
		groups_per_page = 1;

	/* allocate buffer_heads to read bitmaps */
	if (groups_per_page > 1) {
		err = -ENOMEM;
		i = sizeof(struct buffer_head *) * groups_per_page;
		bh = kzalloc(i, GFP_NOFS);
		if (bh == NULL)
			goto out;
	} else
		bh = &bhs;

	first_group = page->index * blocks_per_page / 2;

	/* read all groups the page covers into the cache */
	for (i = 0; i < groups_per_page; i++) {
		struct ext4_group_desc *desc;

		if (first_group + i >= ngroups)
			break;

		grinfo = ext4_get_group_info(sb, first_group + i);
		/*
		 * If page is uptodate then we came here after online resize
		 * which added some new uninitialized group info structs, so
		 * we must skip all initialized uptodate buddies on the page,
		 * which may be currently in use by an allocating task.
		 */
		if (PageUptodate(page) && !EXT4_MB_GRP_NEED_INIT(grinfo)) {
			bh[i] = NULL;
			continue;
		}

		err = -EIO;
		desc = ext4_get_group_desc(sb, first_group + i, NULL);
		if (desc == NULL)
			goto out;

		err = -ENOMEM;
		bh[i] = sb_getblk(sb, ext4_block_bitmap(sb, desc));
		if (bh[i] == NULL)
			goto out;

		if (bitmap_uptodate(bh[i]))
			continue;

		lock_buffer(bh[i]);
		if (bitmap_uptodate(bh[i])) {
			unlock_buffer(bh[i]);
			continue;
		}
		ext4_lock_group(sb, first_group + i);
		if (desc->bg_flags & cpu_to_le16(EXT4_BG_BLOCK_UNINIT)) {
			ext4_init_block_bitmap(sb, bh[i],
						first_group + i, desc);
			set_bitmap_uptodate(bh[i]);
			set_buffer_uptodate(bh[i]);
			ext4_unlock_group(sb, first_group + i);
			unlock_buffer(bh[i]);
			continue;
		}
		ext4_unlock_group(sb, first_group + i);
		if (buffer_uptodate(bh[i])) {
			/*
			 * if not uninit if bh is uptodate,
			 * bitmap is also uptodate
			 */
			set_bitmap_uptodate(bh[i]);
			unlock_buffer(bh[i]);
			continue;
		}
		get_bh(bh[i]);
		/*
		 * submit the buffer_head for read. We can
		 * safely mark the bitmap as uptodate now.
		 * We do it here so the bitmap uptodate bit
		 * get set with buffer lock held.
		 */
		set_bitmap_uptodate(bh[i]);
		bh[i]->b_end_io = end_buffer_read_sync;
		submit_bh(READ, bh[i]);
		mb_debug(1, "read bitmap for group %u\n", first_group + i);
	}

	/* wait for I/O completion */
	for (i = 0; i < groups_per_page; i++)
		if (bh[i])
			wait_on_buffer(bh[i]);

	err = -EIO;
	for (i = 0; i < groups_per_page; i++)
		if (bh[i] && !buffer_uptodate(bh[i]))
			goto out;

	err = 0;
	first_block = page->index * blocks_per_page;
	for (i = 0; i < blocks_per_page; i++) {
		int group;

		group = (first_block + i) >> 1;
		if (group >= ngroups)
			break;

		if (!bh[group - first_group])
			/* skip initialized uptodate buddy */
			continue;

		/*
		 * data carry information regarding this
		 * particular group in the format specified
		 * above
		 *
		 */
		data = page_address(page) + (i * blocksize);
		bitmap = bh[group - first_group]->b_data;

		/*
		 * We place the buddy block and bitmap block
		 * close together
		 */
		if ((first_block + i) & 1) {
			/* this is block of buddy */
			BUG_ON(incore == NULL);
			mb_debug(1, "put buddy for group %u in page %lu/%x\n",
				group, page->index, i * blocksize);
			grinfo = ext4_get_group_info(sb, group);
			grinfo->bb_fragments = 0;
			memset(grinfo->bb_counters, 0,
			       sizeof(*grinfo->bb_counters) *
				(sb->s_blocksize_bits+2));
			/*
			 * incore got set to the group block bitmap below
			 */
			ext4_lock_group(sb, group);
			/* init the buddy */
			memset(data, 0xff, blocksize);
			ext4_mb_generate_buddy(sb, data, incore, group);
			ext4_unlock_group(sb, group);
			incore = NULL;
		} else {
			/* this is block of bitmap */
			BUG_ON(incore != NULL);
			mb_debug(1, "put bitmap for group %u in page %lu/%x\n",
				group, page->index, i * blocksize);

			/* see comments in ext4_mb_put_pa() */
			ext4_lock_group(sb, group);
			memcpy(data, bitmap, blocksize);

			/* mark all preallocated blks used in in-core bitmap */
			ext4_mb_generate_from_pa(sb, data, group);
			ext4_mb_generate_from_freelist(sb, data, group);
			ext4_unlock_group(sb, group);

			/* set incore so that the buddy information can be
			 * generated using this
			 */
			incore = data;
		}
	}
	SetPageUptodate(page);

out:
	if (bh) {
		for (i = 0; i < groups_per_page; i++)
			brelse(bh[i]);
		if (bh != &bhs)
			kfree(bh);
	}
	return err;
}