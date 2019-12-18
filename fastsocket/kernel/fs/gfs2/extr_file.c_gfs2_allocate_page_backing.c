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
typedef  int u64 ;
struct page {int index; TYPE_1__* mapping; } ;
struct inode {int i_blkbits; } ;
struct buffer_head {unsigned long b_size; scalar_t__ b_state; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int PAGE_CACHE_SHIFT ; 
 unsigned long PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_block_map (struct inode*,int,struct buffer_head*,int) ; 

__attribute__((used)) static int gfs2_allocate_page_backing(struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct buffer_head bh;
	unsigned long size = PAGE_CACHE_SIZE;
	u64 lblock = page->index << (PAGE_CACHE_SHIFT - inode->i_blkbits);

	do {
		bh.b_state = 0;
		bh.b_size = size;
		gfs2_block_map(inode, lblock, &bh, 1);
		if (!buffer_mapped(&bh))
			return -EIO;
		size -= bh.b_size;
		lblock += (bh.b_size >> inode->i_blkbits);
	} while(size > 0);
	return 0;
}