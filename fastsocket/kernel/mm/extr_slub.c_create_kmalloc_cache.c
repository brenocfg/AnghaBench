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
struct kmem_cache {int /*<<< orphan*/  list; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_KMALLOC_MINALIGN ; 
 unsigned int SLAB_CACHE_DMA ; 
 int SLUB_DMA ; 
 int /*<<< orphan*/  kmem_cache_open (struct kmem_cache*,int,char const*,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,char const*,int) ; 
 int /*<<< orphan*/  slab_caches ; 
 scalar_t__ sysfs_slab_add (struct kmem_cache*) ; 

__attribute__((used)) static struct kmem_cache *create_kmalloc_cache(struct kmem_cache *s,
		const char *name, int size, gfp_t gfp_flags)
{
	unsigned int flags = 0;

	if (gfp_flags & SLUB_DMA)
		flags = SLAB_CACHE_DMA;

	/*
	 * This function is called with IRQs disabled during early-boot on
	 * single CPU so there's no need to take slub_lock here.
	 */
	if (!kmem_cache_open(s, gfp_flags, name, size, ARCH_KMALLOC_MINALIGN,
								flags, NULL))
		goto panic;

	list_add(&s->list, &slab_caches);

	if (sysfs_slab_add(s))
		goto panic;
	return s;

panic:
	panic("Creation of kmalloc slab %s size=%d failed.\n", name, size);
}