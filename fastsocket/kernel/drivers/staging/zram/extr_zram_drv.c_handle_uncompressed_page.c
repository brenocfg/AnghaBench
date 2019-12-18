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
typedef  size_t u32 ;
struct zram {TYPE_1__* table; } ;
struct page {int dummy; } ;
struct bio_vec {int bv_offset; int /*<<< orphan*/  bv_len; struct page* bv_page; } ;
struct TYPE_2__ {struct page* page; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  KM_USER1 ; 
 int /*<<< orphan*/  flush_dcache_page (struct page*) ; 
 unsigned char* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_uncompressed_page(struct zram *zram, struct bio_vec *bvec,
				     u32 index, int offset)
{
	struct page *page = bvec->bv_page;
	unsigned char *user_mem, *cmem;

	user_mem = kmap_atomic(page, KM_USER0);
	cmem = kmap_atomic(zram->table[index].page, KM_USER1);

	memcpy(user_mem + bvec->bv_offset, cmem + offset, bvec->bv_len);
	kunmap_atomic(cmem, KM_USER1);
	kunmap_atomic(user_mem, KM_USER0);

	flush_dcache_page(page);
}