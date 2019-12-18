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
typedef  unsigned int u64 ;
struct btrfsic_block_data_ctx {unsigned int len; int /*<<< orphan*/ ** datav; int /*<<< orphan*/ ** pagev; int /*<<< orphan*/ * mem_to_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int PAGE_CACHE_SHIFT ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btrfsic_release_block_ctx(struct btrfsic_block_data_ctx *block_ctx)
{
	if (block_ctx->mem_to_free) {
		unsigned int num_pages;

		BUG_ON(!block_ctx->datav);
		BUG_ON(!block_ctx->pagev);
		num_pages = (block_ctx->len + (u64)PAGE_CACHE_SIZE - 1) >>
			    PAGE_CACHE_SHIFT;
		while (num_pages > 0) {
			num_pages--;
			if (block_ctx->datav[num_pages]) {
				kunmap(block_ctx->pagev[num_pages]);
				block_ctx->datav[num_pages] = NULL;
			}
			if (block_ctx->pagev[num_pages]) {
				__free_page(block_ctx->pagev[num_pages]);
				block_ctx->pagev[num_pages] = NULL;
			}
		}

		kfree(block_ctx->mem_to_free);
		block_ctx->mem_to_free = NULL;
		block_ctx->pagev = NULL;
		block_ctx->datav = NULL;
	}
}