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
struct kmem_cache {int dummy; } ;
struct TYPE_2__ {unsigned int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned int PF_MEMALLOC ; 
 TYPE_1__* current ; 
 void* kmem_cache_alloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *iommu_kmem_cache_alloc(struct kmem_cache *cachep)
{
	unsigned int flags;
	void *vaddr;

	/* trying to avoid low memory issues */
	flags = current->flags & PF_MEMALLOC;
	current->flags |= PF_MEMALLOC;
	vaddr = kmem_cache_alloc(cachep, GFP_ATOMIC);
	current->flags &= (~PF_MEMALLOC | flags);
	return vaddr;
}