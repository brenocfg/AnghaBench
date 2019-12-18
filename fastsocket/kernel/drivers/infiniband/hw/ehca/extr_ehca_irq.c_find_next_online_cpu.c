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
struct ehca_comp_pool {int last_cpu; int /*<<< orphan*/  last_cpu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpumask_first (int /*<<< orphan*/ ) ; 
 int cpumask_next (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_size () ; 
 int ehca_debug_level ; 
 int /*<<< orphan*/  ehca_dmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int nr_cpu_ids ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline int find_next_online_cpu(struct ehca_comp_pool *pool)
{
	int cpu;
	unsigned long flags;

	WARN_ON_ONCE(!in_interrupt());
	if (ehca_debug_level >= 3)
		ehca_dmp(cpu_online_mask, cpumask_size(), "");

	spin_lock_irqsave(&pool->last_cpu_lock, flags);
	cpu = cpumask_next(pool->last_cpu, cpu_online_mask);
	if (cpu >= nr_cpu_ids)
		cpu = cpumask_first(cpu_online_mask);
	pool->last_cpu = cpu;
	spin_unlock_irqrestore(&pool->last_cpu_lock, flags);

	return cpu;
}