#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct xv_pool {int /*<<< orphan*/  flbitmap; int /*<<< orphan*/ * slbitmap; TYPE_1__* freelist; } ;
struct page {int dummy; } ;
struct TYPE_4__ {size_t prev_offset; size_t next_offset; struct page* next_page; struct page* prev_page; } ;
struct block_header {TYPE_2__ link; } ;
struct TYPE_3__ {size_t offset; struct page* page; } ;

/* Variables and functions */
 size_t BITS_PER_LONG ; 
 int /*<<< orphan*/  KM_USER1 ; 
 int /*<<< orphan*/  __clear_bit (size_t,int /*<<< orphan*/ *) ; 
 struct block_header* get_ptr_atomic (struct page*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ptr_atomic (struct block_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_block(struct xv_pool *pool, struct page *page, u32 offset,
			struct block_header *block, u32 slindex)
{
	u32 flindex = slindex / BITS_PER_LONG;
	struct block_header *tmpblock;

	if (block->link.prev_page) {
		tmpblock = get_ptr_atomic(block->link.prev_page,
				block->link.prev_offset, KM_USER1);
		tmpblock->link.next_page = block->link.next_page;
		tmpblock->link.next_offset = block->link.next_offset;
		put_ptr_atomic(tmpblock, KM_USER1);
	}

	if (block->link.next_page) {
		tmpblock = get_ptr_atomic(block->link.next_page,
				block->link.next_offset, KM_USER1);
		tmpblock->link.prev_page = block->link.prev_page;
		tmpblock->link.prev_offset = block->link.prev_offset;
		put_ptr_atomic(tmpblock, KM_USER1);
	}

	/* Is this block is at the head of the freelist? */
	if (pool->freelist[slindex].page == page
	   && pool->freelist[slindex].offset == offset) {

		pool->freelist[slindex].page = block->link.next_page;
		pool->freelist[slindex].offset = block->link.next_offset;

		if (pool->freelist[slindex].page) {
			struct block_header *tmpblock;
			tmpblock = get_ptr_atomic(pool->freelist[slindex].page,
					pool->freelist[slindex].offset,
					KM_USER1);
			tmpblock->link.prev_page = NULL;
			tmpblock->link.prev_offset = 0;
			put_ptr_atomic(tmpblock, KM_USER1);
		} else {
			/* This freelist bucket is empty */
			__clear_bit(slindex % BITS_PER_LONG,
				    &pool->slbitmap[flindex]);
			if (!pool->slbitmap[flindex])
				__clear_bit(flindex, &pool->flbitmap);
		}
	}

	block->link.prev_page = NULL;
	block->link.prev_offset = 0;
	block->link.next_page = NULL;
	block->link.next_offset = 0;
}