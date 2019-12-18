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
typedef  scalar_t__ u32 ;
struct xv_pool {int /*<<< orphan*/  lock; } ;
struct page {int dummy; } ;
struct block_header {scalar_t__ size; } ;
typedef  int gfp_t ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BLOCK_FREE ; 
 struct block_header* BLOCK_NEXT (struct block_header*) ; 
 int ENOMEM ; 
 int GFP_NOWAIT ; 
 int /*<<< orphan*/  KM_USER0 ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PREV_FREE ; 
 scalar_t__ XV_ALIGN ; 
 scalar_t__ XV_MAX_ALLOC_SIZE ; 
 scalar_t__ XV_MIN_ALLOC_SIZE ; 
 int /*<<< orphan*/  clear_flag (struct block_header*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_block (struct xv_pool*,scalar_t__,struct page**,scalar_t__*) ; 
 struct block_header* get_ptr_atomic (struct page*,scalar_t__,int /*<<< orphan*/ ) ; 
 int grow_pool (struct xv_pool*,int) ; 
 int /*<<< orphan*/  insert_block (struct xv_pool*,struct page*,scalar_t__,struct block_header*) ; 
 int /*<<< orphan*/  put_ptr_atomic (struct block_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_block (struct xv_pool*,struct page*,scalar_t__,struct block_header*,scalar_t__) ; 
 int /*<<< orphan*/  set_blockprev (struct block_header*,scalar_t__) ; 
 int /*<<< orphan*/  set_flag (struct block_header*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int xv_malloc(struct xv_pool *pool, u32 size, struct page **page,
		u32 *offset, gfp_t flags)
{
	int error;
	u32 index, tmpsize, origsize, tmpoffset;
	struct block_header *block, *tmpblock;

	*page = NULL;
	*offset = 0;
	origsize = size;

	if (unlikely(!size || size > XV_MAX_ALLOC_SIZE))
		return -ENOMEM;

	size = ALIGN(size, XV_ALIGN);

	spin_lock(&pool->lock);

	index = find_block(pool, size, page, offset);

	if (!*page) {
		spin_unlock(&pool->lock);
		if (flags & GFP_NOWAIT)
			return -ENOMEM;
		error = grow_pool(pool, flags);
		if (unlikely(error))
			return error;

		spin_lock(&pool->lock);
		index = find_block(pool, size, page, offset);
	}

	if (!*page) {
		spin_unlock(&pool->lock);
		return -ENOMEM;
	}

	block = get_ptr_atomic(*page, *offset, KM_USER0);

	remove_block(pool, *page, *offset, block, index);

	/* Split the block if required */
	tmpoffset = *offset + size + XV_ALIGN;
	tmpsize = block->size - size;
	tmpblock = (struct block_header *)((char *)block + size + XV_ALIGN);
	if (tmpsize) {
		tmpblock->size = tmpsize - XV_ALIGN;
		set_flag(tmpblock, BLOCK_FREE);
		clear_flag(tmpblock, PREV_FREE);

		set_blockprev(tmpblock, *offset);
		if (tmpblock->size >= XV_MIN_ALLOC_SIZE)
			insert_block(pool, *page, tmpoffset, tmpblock);

		if (tmpoffset + XV_ALIGN + tmpblock->size != PAGE_SIZE) {
			tmpblock = BLOCK_NEXT(tmpblock);
			set_blockprev(tmpblock, tmpoffset);
		}
	} else {
		/* This block is exact fit */
		if (tmpoffset != PAGE_SIZE)
			clear_flag(tmpblock, PREV_FREE);
	}

	block->size = origsize;
	clear_flag(block, BLOCK_FREE);

	put_ptr_atomic(block, KM_USER0);
	spin_unlock(&pool->lock);

	*offset += XV_ALIGN;

	return 0;
}