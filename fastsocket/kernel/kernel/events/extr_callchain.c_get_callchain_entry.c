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
struct perf_callchain_entry {int dummy; } ;
struct callchain_cpus_entries {struct perf_callchain_entry** cpu_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  __get_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callchain_cpus_entries ; 
 int /*<<< orphan*/  callchain_recursion ; 
 int get_recursion_context (int /*<<< orphan*/ ) ; 
 struct callchain_cpus_entries* rcu_dereference (int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

__attribute__((used)) static struct perf_callchain_entry *get_callchain_entry(int *rctx)
{
	int cpu;
	struct callchain_cpus_entries *entries;

	*rctx = get_recursion_context(__get_cpu_var(callchain_recursion));
	if (*rctx == -1)
		return NULL;

	entries = rcu_dereference(callchain_cpus_entries);
	if (!entries)
		return NULL;

	cpu = smp_processor_id();

	return &entries->cpu_entries[cpu][*rctx];
}