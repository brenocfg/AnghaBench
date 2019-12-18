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
struct kmem_cache {int size; int /*<<< orphan*/  flags; int /*<<< orphan*/  (* ctor ) (void*) ;int /*<<< orphan*/  align; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int SLOB_UNIT ; 
 int SLOB_UNITS (int) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int get_order (int) ; 
 int /*<<< orphan*/  kmemleak_alloc_recursive (void*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* slob_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* slob_new_pages (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  trace_kmem_cache_alloc_node (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ ,int) ; 

void *kmem_cache_alloc_node(struct kmem_cache *c, gfp_t flags, int node)
{
	void *b;

	if (c->size < PAGE_SIZE) {
		b = slob_alloc(c->size, flags, c->align, node);
		trace_kmem_cache_alloc_node(_RET_IP_, b, c->size,
					    SLOB_UNITS(c->size) * SLOB_UNIT,
					    flags, node);
	} else {
		b = slob_new_pages(flags, get_order(c->size), node);
		trace_kmem_cache_alloc_node(_RET_IP_, b, c->size,
					    PAGE_SIZE << get_order(c->size),
					    flags, node);
	}

	if (c->ctor)
		c->ctor(b);

	kmemleak_alloc_recursive(b, c->size, 1, c->flags, flags);
	return b;
}