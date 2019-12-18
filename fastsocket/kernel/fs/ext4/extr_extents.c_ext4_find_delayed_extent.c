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
struct page {int index; } ;
struct inode {int /*<<< orphan*/  i_mapping; TYPE_1__* i_sb; } ;
struct ext4_ext_cache {int ec_block; int ec_len; scalar_t__ ec_start; } ;
struct buffer_head {struct buffer_head* b_this_page; } ;
typedef  int pgoff_t ;
typedef  int ext4_lblk_t ;
typedef  unsigned char __u64 ;
typedef  int __u32 ;
struct TYPE_2__ {unsigned char s_blocksize_bits; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int EXT_INIT_MAX_LEN ; 
 int EXT_MAX_BLOCKS ; 
 int FIEMAP_EXTENT_DELALLOC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGECACHE_TAG_DIRTY ; 
 unsigned char PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ buffer_delay (struct buffer_head*) ; 
 scalar_t__ buffer_mapped (struct buffer_head*) ; 
 int find_get_pages_tag (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,unsigned int,struct page**) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int min (int,int) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 

__attribute__((used)) static int ext4_find_delayed_extent(struct inode *inode,
				    struct ext4_ext_cache *newex)
{
	__u32		flags = 0;
	int		ret = 0;
	ext4_lblk_t	next_start = EXT_MAX_BLOCKS;
	unsigned int	next_len;
	unsigned char blksize_bits = inode->i_sb->s_blocksize_bits;

	/*
	 * No extent in extent-tree contains block @newex->ec_start,
	 * then the block may stay in 1)a hole or 2)delayed-extent.
	 *
	 * Holes or delayed-extents are processed as follows.
	 * 1. lookup dirty pages with specified range in pagecache.
	 *    If no page is got, then there is no delayed-extent and
	 *    return with EXT_CONTINUE.
	 * 2. find the 1st mapped buffer,
	 * 3. check if the mapped buffer is both in the request range
	 *    and a delayed buffer. If not, there is no delayed-extent,
	 *    then return.
	 * 4. a delayed-extent is found, the extent will be collected.
	 */
	ext4_lblk_t	end = 0;
	pgoff_t		last_offset;
	pgoff_t		offset;
	pgoff_t		index;
	struct page	**pages = NULL;
	struct buffer_head *bh = NULL;
	struct buffer_head *head = NULL;
	unsigned int nr_pages = PAGE_SIZE / sizeof(struct page *);

	pages = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (pages == NULL)
		return -ENOMEM;

	offset = ((__u64)newex->ec_block << blksize_bits) >>
			PAGE_SHIFT;

repeat:
	last_offset = offset;
	head = NULL;
	ret = find_get_pages_tag(inode->i_mapping, &offset,
				PAGECACHE_TAG_DIRTY, nr_pages, pages);

	if (!(flags & FIEMAP_EXTENT_DELALLOC)) {
		/* First time, try to find a mapped buffer. */
		if (ret == 0) {
out:
			for (index = 0; index < ret; index++)
				page_cache_release(pages[index]);
			/* just a hole. */
			kfree(pages);
			return EXT_MAX_BLOCKS;
		}

		/* Try to find the 1st mapped buffer. */
		end = ((__u64)pages[0]->index << PAGE_SHIFT) >>
			  blksize_bits;
		if (!page_has_buffers(pages[0]))
			goto out;
		head = page_buffers(pages[0]);
		if (!head)
			goto out;

		bh = head;
		do {
			if (buffer_mapped(bh) &&
			    (end >= newex->ec_block)) {
				/* get the 1st mapped buffer. */
				if (end > newex->ec_block +
					newex->ec_len)
					/* The buffer is out of
					 * the request range.
					 */
					goto out;
				goto found_mapped_buffer;
			}
			bh = bh->b_this_page;
			end++;
		} while (bh != head);

		/* No mapped buffer found. */
		goto out;
	} else {
		/*Find contiguous delayed buffers. */
		if (ret > 0 && pages[0]->index == last_offset)
			head = page_buffers(pages[0]);
		bh = head;
	}

found_mapped_buffer:
	if (bh != NULL && buffer_delay(bh)) {
		/* 1st or contiguous delayed buffer found. */
		if (!(flags & FIEMAP_EXTENT_DELALLOC)) {
			/*
			 * 1st delayed buffer found, record
			 * the start of extent.
			 */
			flags |= FIEMAP_EXTENT_DELALLOC;
			next_start = end;
		}
		/* Find contiguous delayed buffers. */
		do {
			if (!buffer_delay(bh))
				goto found_delayed_extent;
			bh = bh->b_this_page;
			end++;
		} while (bh != head);

		for (index = 1; index < ret; index++) {
			if (!page_has_buffers(pages[index])) {
				bh = NULL;
				break;
			}
			head = page_buffers(pages[index]);
			if (!head) {
				bh = NULL;
				break;
			}
			if (pages[index]->index !=
				pages[0]->index + index) {
				/* Blocks are not contiguous. */
				bh = NULL;
				break;
			}
			bh = head;
			do {
				if (!buffer_delay(bh))
					/* Delayed-extent ends. */
					goto found_delayed_extent;
				bh = bh->b_this_page;
				end++;
			} while (bh != head);
		}
	} else if (!(flags & FIEMAP_EXTENT_DELALLOC))
		/* a hole found. */
		goto out;

found_delayed_extent:
	next_len = min(end - next_start,
		       (ext4_lblk_t)EXT_INIT_MAX_LEN);
	if (ret == nr_pages && bh != NULL &&
		next_len < EXT_INIT_MAX_LEN &&
		buffer_delay(bh)) {
		/* Have not collected an extent and continue. */
		for (index = 0; index < ret; index++)
			page_cache_release(pages[index]);
		goto repeat;
	}

	for (index = 0; index < ret; index++)
		page_cache_release(pages[index]);
	kfree(pages);

	/* If passed extent did not exist, update it with delayed extent */
	if (newex->ec_start == 0) {
		newex->ec_block = next_start;
		newex->ec_len = next_len;
	}

	return next_start;
}