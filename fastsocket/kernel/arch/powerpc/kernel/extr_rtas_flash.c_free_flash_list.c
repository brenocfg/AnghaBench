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
struct flash_block_list {int num_blocks; struct flash_block_list* next; TYPE_1__* blocks; } ;
struct TYPE_2__ {struct flash_block_list* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  flash_block_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct flash_block_list*) ; 

__attribute__((used)) static void free_flash_list(struct flash_block_list *f)
{
	struct flash_block_list *next;
	int i;

	while (f) {
		for (i = 0; i < f->num_blocks; i++)
			kmem_cache_free(flash_block_cache, f->blocks[i].data);
		next = f->next;
		kmem_cache_free(flash_block_cache, f);
		f = next;
	}
}