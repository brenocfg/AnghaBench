#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bitmap_storage {int file_pages; scalar_t__ sb_page; int /*<<< orphan*/ * file; } ;
struct bitmap_page {int dummy; } ;
struct bitmap_counts {unsigned long chunks; int chunkshift; long pages; long missing_pages; int /*<<< orphan*/  lock; struct bitmap_page* bp; } ;
struct bitmap {TYPE_3__* mddev; struct bitmap_counts counts; struct bitmap_storage storage; } ;
typedef  int /*<<< orphan*/  store ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  bitmap_super_t ;
typedef  int bitmap_counter_t ;
struct TYPE_6__ {long space; int chunksize; int /*<<< orphan*/  external; scalar_t__ file; scalar_t__ offset; } ;
struct TYPE_7__ {TYPE_1__* pers; TYPE_2__ bitmap_info; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* quiesce ) (TYPE_3__*,int) ;} ;

/* Variables and functions */
 int BITMAP_BLOCK_SHIFT ; 
 int /*<<< orphan*/  BITMAP_PAGE_DIRTY ; 
 long DIV_ROUND_UP (unsigned long,int) ; 
 unsigned long DIV_ROUND_UP_SECTOR_T (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NEEDED (int) ; 
 int NEEDED_MASK ; 
 int PAGE_COUNTER_RATIO ; 
 int /*<<< orphan*/  bitmap_count_page (struct bitmap_counts*,int,int) ; 
 int /*<<< orphan*/  bitmap_file_set_bit (struct bitmap*,int) ; 
 int /*<<< orphan*/  bitmap_file_unmap (struct bitmap_storage*) ; 
 int* bitmap_get_counter (struct bitmap_counts*,int,int*,int) ; 
 int /*<<< orphan*/  bitmap_set_pending (struct bitmap_counts*,int) ; 
 int bitmap_storage_alloc (struct bitmap_storage*,unsigned long,int) ; 
 int /*<<< orphan*/  bitmap_unplug (struct bitmap*) ; 
 int ffz (int) ; 
 struct bitmap_page* kzalloc (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct bitmap_storage*,int /*<<< orphan*/ ,int) ; 
 int min (int,unsigned long) ; 
 int /*<<< orphan*/  page_address (scalar_t__) ; 
 int /*<<< orphan*/  set_page_attr (struct bitmap*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int) ; 

int bitmap_resize(struct bitmap *bitmap, sector_t blocks,
		  int chunksize, int init)
{
	/* If chunk_size is 0, choose an appropriate chunk size.
	 * Then possibly allocate new storage space.
	 * Then quiesce, copy bits, replace bitmap, and re-start
	 *
	 * This function is called both to set up the initial bitmap
	 * and to resize the bitmap while the array is active.
	 * If this happens as a result of the array being resized,
	 * chunksize will be zero, and we need to choose a suitable
	 * chunksize, otherwise we use what we are given.
	 */
	struct bitmap_storage store;
	struct bitmap_counts old_counts;
	unsigned long chunks;
	sector_t block;
	sector_t old_blocks, new_blocks;
	int chunkshift;
	int ret = 0;
	long pages;
	struct bitmap_page *new_bp;

	if (chunksize == 0) {
		/* If there is enough space, leave the chunk size unchanged,
		 * else increase by factor of two until there is enough space.
		 */
		long bytes;
		long space = bitmap->mddev->bitmap_info.space;

		if (space == 0) {
			/* We don't know how much space there is, so limit
			 * to current size - in sectors.
			 */
			bytes = DIV_ROUND_UP(bitmap->counts.chunks, 8);
			if (!bitmap->mddev->bitmap_info.external)
				bytes += sizeof(bitmap_super_t);
			space = DIV_ROUND_UP(bytes, 512);
			bitmap->mddev->bitmap_info.space = space;
		}
		chunkshift = bitmap->counts.chunkshift;
		chunkshift--;
		do {
			/* 'chunkshift' is shift from block size to chunk size */
			chunkshift++;
			chunks = DIV_ROUND_UP_SECTOR_T(blocks, 1 << chunkshift);
			bytes = DIV_ROUND_UP(chunks, 8);
			if (!bitmap->mddev->bitmap_info.external)
				bytes += sizeof(bitmap_super_t);
		} while (bytes > (space << 9));
	} else
		chunkshift = ffz(~chunksize) - BITMAP_BLOCK_SHIFT;

	chunks = DIV_ROUND_UP_SECTOR_T(blocks, 1 << chunkshift);
	memset(&store, 0, sizeof(store));
	if (bitmap->mddev->bitmap_info.offset || bitmap->mddev->bitmap_info.file)
		ret = bitmap_storage_alloc(&store, chunks,
					   !bitmap->mddev->bitmap_info.external);
	if (ret)
		goto err;

	pages = DIV_ROUND_UP(chunks, PAGE_COUNTER_RATIO);

	new_bp = kzalloc(pages * sizeof(*new_bp), GFP_KERNEL);
	ret = -ENOMEM;
	if (!new_bp) {
		bitmap_file_unmap(&store);
		goto err;
	}

	if (!init)
		bitmap->mddev->pers->quiesce(bitmap->mddev, 1);

	store.file = bitmap->storage.file;
	bitmap->storage.file = NULL;

	if (store.sb_page && bitmap->storage.sb_page)
		memcpy(page_address(store.sb_page),
		       page_address(bitmap->storage.sb_page),
		       sizeof(bitmap_super_t));
	bitmap_file_unmap(&bitmap->storage);
	bitmap->storage = store;

	old_counts = bitmap->counts;
	bitmap->counts.bp = new_bp;
	bitmap->counts.pages = pages;
	bitmap->counts.missing_pages = pages;
	bitmap->counts.chunkshift = chunkshift;
	bitmap->counts.chunks = chunks;
	bitmap->mddev->bitmap_info.chunksize = 1 << (chunkshift +
						     BITMAP_BLOCK_SHIFT);

	blocks = min(old_counts.chunks << old_counts.chunkshift,
		     chunks << chunkshift);

	spin_lock_irq(&bitmap->counts.lock);
	for (block = 0; block < blocks; ) {
		bitmap_counter_t *bmc_old, *bmc_new;
		int set;

		bmc_old = bitmap_get_counter(&old_counts, block,
					     &old_blocks, 0);
		set = bmc_old && NEEDED(*bmc_old);

		if (set) {
			bmc_new = bitmap_get_counter(&bitmap->counts, block,
						     &new_blocks, 1);
			if (*bmc_new == 0) {
				/* need to set on-disk bits too. */
				sector_t end = block + new_blocks;
				sector_t start = block >> chunkshift;
				start <<= chunkshift;
				while (start < end) {
					bitmap_file_set_bit(bitmap, block);
					start += 1 << chunkshift;
				}
				*bmc_new = 2;
				bitmap_count_page(&bitmap->counts,
						  block, 1);
				bitmap_set_pending(&bitmap->counts,
						   block);
			}
			*bmc_new |= NEEDED_MASK;
			if (new_blocks < old_blocks)
				old_blocks = new_blocks;
		}
		block += old_blocks;
	}

	if (!init) {
		int i;
		while (block < (chunks << chunkshift)) {
			bitmap_counter_t *bmc;
			bmc = bitmap_get_counter(&bitmap->counts, block,
						 &new_blocks, 1);
			if (bmc) {
				/* new space.  It needs to be resynced, so
				 * we set NEEDED_MASK.
				 */
				if (*bmc == 0) {
					*bmc = NEEDED_MASK | 2;
					bitmap_count_page(&bitmap->counts,
							  block, 1);
					bitmap_set_pending(&bitmap->counts,
							   block);
				}
			}
			block += new_blocks;
		}
		for (i = 0; i < bitmap->storage.file_pages; i++)
			set_page_attr(bitmap, i, BITMAP_PAGE_DIRTY);
	}
	spin_unlock_irq(&bitmap->counts.lock);

	if (!init) {
		bitmap_unplug(bitmap);
		bitmap->mddev->pers->quiesce(bitmap->mddev, 0);
	}
	ret = 0;
err:
	return ret;
}