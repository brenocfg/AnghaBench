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
struct xv_pool {int /*<<< orphan*/  lock; int /*<<< orphan*/  total_pages; } ;
struct page {int dummy; } ;
struct block_header {scalar_t__ size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FREE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_USER0 ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PREV_FREE ; 
 scalar_t__ XV_ALIGN ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_flag (struct block_header*,int /*<<< orphan*/ ) ; 
 struct block_header* get_ptr_atomic (struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_block (struct xv_pool*,struct page*,int /*<<< orphan*/ ,struct block_header*) ; 
 int /*<<< orphan*/  put_ptr_atomic (struct block_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_blockprev (struct block_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_flag (struct block_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int grow_pool(struct xv_pool *pool, gfp_t flags)
{
	struct page *page;
	struct block_header *block;

	page = alloc_page(flags);
	if (unlikely(!page))
		return -ENOMEM;

	stat_inc(&pool->total_pages);

	spin_lock(&pool->lock);
	block = get_ptr_atomic(page, 0, KM_USER0);

	block->size = PAGE_SIZE - XV_ALIGN;
	set_flag(block, BLOCK_FREE);
	clear_flag(block, PREV_FREE);
	set_blockprev(block, 0);

	insert_block(pool, page, 0, block);

	put_ptr_atomic(block, KM_USER0);
	spin_unlock(&pool->lock);

	return 0;
}