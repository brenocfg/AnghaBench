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
struct page {int dummy; } ;
struct buffer_head {unsigned long b_state; struct buffer_head* b_this_page; struct block_device* b_bdev; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 unsigned long BH_NILFS_Allocated ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 struct buffer_head* alloc_page_buffers (struct page*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  attach_page_buffers (struct page*,struct buffer_head*) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

struct page *nilfs_alloc_private_page(struct block_device *bdev, int size,
				      unsigned long state)
{
	struct buffer_head *bh, *head, *tail;
	struct page *page;

	page = alloc_page(GFP_NOFS); /* page_count of the returned page is 1 */
	if (unlikely(!page))
		return NULL;

	lock_page(page);
	head = alloc_page_buffers(page, size, 0);
	if (unlikely(!head)) {
		unlock_page(page);
		__free_page(page);
		return NULL;
	}

	bh = head;
	do {
		bh->b_state = (1UL << BH_NILFS_Allocated) | state;
		tail = bh;
		bh->b_bdev = bdev;
		bh = bh->b_this_page;
	} while (bh);

	tail->b_this_page = head;
	attach_page_buffers(page, head);

	return page;
}