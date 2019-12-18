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
typedef  size_t u64 ;
typedef  size_t u32 ;
struct btrfsic_block_data_ctx {size_t start; size_t len; char** datav; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 size_t PAGE_CACHE_SHIFT ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t min (size_t,size_t) ; 

__attribute__((used)) static void btrfsic_read_from_block_data(
	struct btrfsic_block_data_ctx *block_ctx,
	void *dstv, u32 offset, size_t len)
{
	size_t cur;
	size_t offset_in_page;
	char *kaddr;
	char *dst = (char *)dstv;
	size_t start_offset = block_ctx->start & ((u64)PAGE_CACHE_SIZE - 1);
	unsigned long i = (start_offset + offset) >> PAGE_CACHE_SHIFT;

	WARN_ON(offset + len > block_ctx->len);
	offset_in_page = (start_offset + offset) &
			 ((unsigned long)PAGE_CACHE_SIZE - 1);

	while (len > 0) {
		cur = min(len, ((size_t)PAGE_CACHE_SIZE - offset_in_page));
		BUG_ON(i >= (block_ctx->len + PAGE_CACHE_SIZE - 1) >>
			    PAGE_CACHE_SHIFT);
		kaddr = block_ctx->datav[i];
		memcpy(dst, kaddr + offset_in_page, cur);

		dst += cur;
		len -= cur;
		offset_in_page = 0;
		i++;
	}
}