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
typedef  int /*<<< orphan*/  ulong ;
typedef  size_t u32 ;
struct TYPE_4__ {int /*<<< orphan*/  failed_reads; } ;
struct zram {TYPE_2__ stats; TYPE_1__* table; } ;
struct zobj_header {int dummy; } ;
struct page {int dummy; } ;
struct bio_vec {int bv_offset; int /*<<< orphan*/  bv_len; struct page* bv_page; } ;
struct bio {int /*<<< orphan*/  bi_size; scalar_t__ bi_sector; } ;
struct TYPE_3__ {int offset; struct page* page; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  KM_USER1 ; 
 int LZO_E_OK ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/  ZRAM_UNCOMPRESSED ; 
 int /*<<< orphan*/  ZRAM_ZERO ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 int /*<<< orphan*/  handle_uncompressed_page (struct zram*,struct bio_vec*,size_t,int) ; 
 int /*<<< orphan*/  handle_zero_page (struct bio_vec*) ; 
 scalar_t__ is_partial_io (struct bio_vec*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 unsigned char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned char*,int /*<<< orphan*/ ) ; 
 int lzo1x_decompress_safe (unsigned char*,scalar_t__,unsigned char*,size_t*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,size_t) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ xv_get_object_size (unsigned char*) ; 
 int /*<<< orphan*/  zram_stat64_inc (struct zram*,int /*<<< orphan*/ *) ; 
 int zram_test_flag (struct zram*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zram_bvec_read(struct zram *zram, struct bio_vec *bvec,
			  u32 index, int offset, struct bio *bio)
{
	int ret;
	size_t clen;
	struct page *page;
	struct zobj_header *zheader;
	unsigned char *user_mem, *cmem, *uncmem = NULL;

	page = bvec->bv_page;

	if (zram_test_flag(zram, index, ZRAM_ZERO)) {
		handle_zero_page(bvec);
		return 0;
	}

	/* Requested page is not present in compressed area */
	if (unlikely(!zram->table[index].page)) {
		pr_debug("Read before write: sector=%lu, size=%u",
			 (ulong)(bio->bi_sector), bio->bi_size);
		handle_zero_page(bvec);
		return 0;
	}

	/* Page is stored uncompressed since it's incompressible */
	if (unlikely(zram_test_flag(zram, index, ZRAM_UNCOMPRESSED))) {
		handle_uncompressed_page(zram, bvec, index, offset);
		return 0;
	}

	if (is_partial_io(bvec)) {
		/* Use  a temporary buffer to decompress the page */
		uncmem = kmalloc(PAGE_SIZE, GFP_KERNEL);
		if (!uncmem) {
			pr_info("Error allocating temp memory!\n");
			return -ENOMEM;
		}
	}

	user_mem = kmap_atomic(page, KM_USER0);
	if (!is_partial_io(bvec))
		uncmem = user_mem;
	clen = PAGE_SIZE;

	cmem = kmap_atomic(zram->table[index].page, KM_USER1) +
		zram->table[index].offset;

	ret = lzo1x_decompress_safe(cmem + sizeof(*zheader),
				    xv_get_object_size(cmem) - sizeof(*zheader),
				    uncmem, &clen);

	if (is_partial_io(bvec)) {
		memcpy(user_mem + bvec->bv_offset, uncmem + offset,
		       bvec->bv_len);
		kfree(uncmem);
	}

	kunmap_atomic(cmem, KM_USER1);
	kunmap_atomic(user_mem, KM_USER0);

	/* Should NEVER happen. Return bio error if it does. */
	if (unlikely(ret != LZO_E_OK)) {
		pr_err("Decompression failed! err=%d, page=%u\n", ret, index);
		zram_stat64_inc(zram, &zram->stats.failed_reads);
		return ret;
	}

	flush_dcache_page(page);

	return 0;
}