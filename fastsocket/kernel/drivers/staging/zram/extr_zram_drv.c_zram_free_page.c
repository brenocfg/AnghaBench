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
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  pages_stored; int /*<<< orphan*/  compr_size; int /*<<< orphan*/  good_compress; int /*<<< orphan*/  pages_expand; int /*<<< orphan*/  pages_zero; } ;
struct zram {TYPE_2__* table; TYPE_1__ stats; int /*<<< orphan*/  mem_pool; } ;
struct zobj_header {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_4__ {int offset; struct page* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  ZRAM_UNCOMPRESSED ; 
 int /*<<< orphan*/  ZRAM_ZERO ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 void* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xv_free (int /*<<< orphan*/ ,struct page*,int) ; 
 int xv_get_object_size (void*) ; 
 int /*<<< orphan*/  zram_clear_flag (struct zram*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zram_stat64_sub (struct zram*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zram_stat_dec (int /*<<< orphan*/ *) ; 
 int zram_test_flag (struct zram*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zram_free_page(struct zram *zram, size_t index)
{
	u32 clen;
	void *obj;

	struct page *page = zram->table[index].page;
	u32 offset = zram->table[index].offset;

	if (unlikely(!page)) {
		/*
		 * No memory is allocated for zero filled pages.
		 * Simply clear zero page flag.
		 */
		if (zram_test_flag(zram, index, ZRAM_ZERO)) {
			zram_clear_flag(zram, index, ZRAM_ZERO);
			zram_stat_dec(&zram->stats.pages_zero);
		}
		return;
	}

	if (unlikely(zram_test_flag(zram, index, ZRAM_UNCOMPRESSED))) {
		clen = PAGE_SIZE;
		__free_page(page);
		zram_clear_flag(zram, index, ZRAM_UNCOMPRESSED);
		zram_stat_dec(&zram->stats.pages_expand);
		goto out;
	}

	obj = kmap_atomic(page, KM_USER0) + offset;
	clen = xv_get_object_size(obj) - sizeof(struct zobj_header);
	kunmap_atomic(obj, KM_USER0);

	xv_free(zram->mem_pool, page, offset);
	if (clen <= PAGE_SIZE / 2)
		zram_stat_dec(&zram->stats.good_compress);

out:
	zram_stat64_sub(zram, &zram->stats.compr_size, clen);
	zram_stat_dec(&zram->stats.pages_stored);

	zram->table[index].page = NULL;
	zram->table[index].offset = 0;
}