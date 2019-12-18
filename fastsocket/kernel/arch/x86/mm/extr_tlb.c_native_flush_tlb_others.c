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
struct mm_struct {int dummy; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_tlb_others_ipi (struct cpumask const*,struct mm_struct*,unsigned long) ; 
 unsigned int get_cpu () ; 
 scalar_t__ is_uv_system () ; 
 int /*<<< orphan*/  put_cpu () ; 
 struct cpumask* uv_flush_tlb_others (struct cpumask const*,struct mm_struct*,unsigned long,unsigned int) ; 

void native_flush_tlb_others(const struct cpumask *cpumask,
			     struct mm_struct *mm, unsigned long va)
{
	if (is_uv_system()) {
		unsigned int cpu;

		cpu = get_cpu();
		cpumask = uv_flush_tlb_others(cpumask, mm, va, cpu);
		if (cpumask)
			flush_tlb_others_ipi(cpumask, mm, va);
		put_cpu();
		return;
	}
	flush_tlb_others_ipi(cpumask, mm, va);
}