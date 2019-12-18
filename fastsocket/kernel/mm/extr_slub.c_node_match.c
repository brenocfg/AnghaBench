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
struct kmem_cache_cpu {int node; } ;

/* Variables and functions */

__attribute__((used)) static inline int node_match(struct kmem_cache_cpu *c, int node)
{
#ifdef CONFIG_NUMA
	if (node != -1 && c->node != node)
		return 0;
#endif
	return 1;
}