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
typedef  int /*<<< orphan*/  cpumask_t ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALIDATE_CACHE_IPI ; 
 int /*<<< orphan*/  _flush_cache_copyback_all () ; 
 int /*<<< orphan*/  atomic_set_mask (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_online_map ; 
 unsigned long* cpus_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ flushcache_cpumask ; 
 int /*<<< orphan*/  flushcache_lock ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  send_IPI_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void smp_flush_cache_all(void)
{
	cpumask_t cpumask;
	unsigned long *mask;

	preempt_disable();
	cpumask = cpu_online_map;
	cpu_clear(smp_processor_id(), cpumask);
	spin_lock(&flushcache_lock);
	mask=cpus_addr(cpumask);
	atomic_set_mask(*mask, (atomic_t *)&flushcache_cpumask);
	send_IPI_mask(&cpumask, INVALIDATE_CACHE_IPI, 0);
	_flush_cache_copyback_all();
	while (flushcache_cpumask)
		mb();
	spin_unlock(&flushcache_lock);
	preempt_enable();
}