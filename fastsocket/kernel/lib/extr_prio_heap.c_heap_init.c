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
struct ptr_heap {size_t max; int (* gt ) (void*,void*) ;scalar_t__ size; int /*<<< orphan*/  ptrs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  kmalloc (size_t,int /*<<< orphan*/ ) ; 

int heap_init(struct ptr_heap *heap, size_t size, gfp_t gfp_mask,
	      int (*gt)(void *, void *))
{
	heap->ptrs = kmalloc(size, gfp_mask);
	if (!heap->ptrs)
		return -ENOMEM;
	heap->size = 0;
	heap->max = size / sizeof(void *);
	heap->gt = gt;
	return 0;
}