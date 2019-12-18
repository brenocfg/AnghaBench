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
struct kmem_cache_cpu {int offset; int /*<<< orphan*/  stat; int /*<<< orphan*/  objsize; scalar_t__ node; int /*<<< orphan*/ * freelist; int /*<<< orphan*/ * page; } ;
struct kmem_cache {int offset; int /*<<< orphan*/  objsize; } ;

/* Variables and functions */
 int NR_SLUB_STAT_ITEMS ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_kmem_cache_cpu(struct kmem_cache *s,
			struct kmem_cache_cpu *c)
{
	c->page = NULL;
	c->freelist = NULL;
	c->node = 0;
	c->offset = s->offset / sizeof(void *);
	c->objsize = s->objsize;
#ifdef CONFIG_SLUB_STATS
	memset(c->stat, 0, NR_SLUB_STAT_ITEMS * sizeof(unsigned));
#endif
}