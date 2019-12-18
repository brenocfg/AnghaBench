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
struct kmem_cache {int /*<<< orphan*/  cpu_slab; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  init_kmem_cache_cpu (struct kmem_cache*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int alloc_kmem_cache_cpus(struct kmem_cache *s, gfp_t flags)
{
	init_kmem_cache_cpu(s, &s->cpu_slab);
	return 1;
}