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
struct list_head {int dummy; } ;
struct chain_allocator {int dummy; } ;
struct bm_block {int /*<<< orphan*/  hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_BITS_PER_BLOCK ; 
 unsigned int DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct bm_block* chain_alloc (struct chain_allocator*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 

__attribute__((used)) static int create_bm_block_list(unsigned long pages,
				struct list_head *list,
				struct chain_allocator *ca)
{
	unsigned int nr_blocks = DIV_ROUND_UP(pages, BM_BITS_PER_BLOCK);

	while (nr_blocks-- > 0) {
		struct bm_block *bb;

		bb = chain_alloc(ca, sizeof(struct bm_block));
		if (!bb)
			return -ENOMEM;
		list_add(&bb->hook, list);
	}

	return 0;
}