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

/* Variables and functions */
 scalar_t__ cfq_ioc_pool ; 
 scalar_t__ cfq_pool ; 
 int /*<<< orphan*/  kmem_cache_destroy (scalar_t__) ; 

__attribute__((used)) static void cfq_slab_kill(void)
{
	/*
	 * Caller already ensured that pending RCU callbacks are completed,
	 * so we should have no busy allocations at this point.
	 */
	if (cfq_pool)
		kmem_cache_destroy(cfq_pool);
	if (cfq_ioc_pool)
		kmem_cache_destroy(cfq_ioc_pool);
}