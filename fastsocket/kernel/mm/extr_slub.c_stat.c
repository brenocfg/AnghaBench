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
struct kmem_cache_cpu {int /*<<< orphan*/ * stat; } ;
typedef  enum stat_item { ____Placeholder_stat_item } stat_item ;

/* Variables and functions */

__attribute__((used)) static inline void stat(struct kmem_cache_cpu *c, enum stat_item si)
{
#ifdef CONFIG_SLUB_STATS
	c->stat[si]++;
#endif
}