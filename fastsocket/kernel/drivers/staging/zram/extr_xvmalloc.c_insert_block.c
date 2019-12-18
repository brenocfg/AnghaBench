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
struct TYPE_4__ {size_t prev_offset; size_t next_offset; struct page* prev_page; struct page* next_page; } ;
struct block_header {TYPE_2__ link; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {size_t offset; struct page* page; } ;

/* Variables and functions */
 size_t BITS_PER_LONG ; 
 int /*<<< orphan*/  KM_USER1 ; 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ *) ; 
 size_t get_index_for_insert (int /*<<< orphan*/ ) ; 
 struct block_header* get_ptr_atomic (struct page*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ptr_atomic (struct block_header*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void insert_block(struct xv_pool *pool, struct page *page, u32 offset,
			struct block_header *block)
{
	u32 flindex, slindex;
	struct block_header *nextblock;

	slindex = get_index_for_insert(block->size);
	flindex = slindex / BITS_PER_LONG;

	block->link.prev_page = NULL;
	block->link.prev_offset = 0;
	block->link.next_page = pool->freelist[slindex].page;
	block->link.next_offset = pool->freelist[slindex].offset;
	pool->freelist[slindex].page = page;
	pool->freelist[slindex].offset = offset;

	if (block->link.next_page) {
		nextblock = get_ptr_atomic(block->link.next_page,
					block->link.next_offset, KM_USER1);
		nextblock->link.prev_page = page;
		nextblock->link.prev_offset = offset;
		put_ptr_atomic(nextblock, KM_USER1);
		/* If there was a next page then the free bits are set. */
		return;
	}

	__set_bit(slindex % BITS_PER_LONG, &pool->slbitmap[flindex]);
	__set_bit(flindex, &pool->flbitmap);
}