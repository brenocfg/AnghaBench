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
struct percpu_data {void** ptrs; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (void*) ; 
 int __GFP_ZERO ; 
 struct percpu_data* __percpu_disguise (void*) ; 
 int /*<<< orphan*/  cache_line_size () ; 
 int cpu_to_node (int) ; 
 void* kmalloc_node (size_t,int,int) ; 
 void* kzalloc (size_t,int) ; 
 scalar_t__ node_online (int) ; 
 size_t roundup (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *percpu_populate(void *__pdata, size_t size, gfp_t gfp, int cpu)
{
	struct percpu_data *pdata = __percpu_disguise(__pdata);
	int node = cpu_to_node(cpu);

	/*
	 * We should make sure each CPU gets private memory.
	 */
	size = roundup(size, cache_line_size());

	BUG_ON(pdata->ptrs[cpu]);
	if (node_online(node))
		pdata->ptrs[cpu] = kmalloc_node(size, gfp|__GFP_ZERO, node);
	else
		pdata->ptrs[cpu] = kzalloc(size, gfp);
	return pdata->ptrs[cpu];
}