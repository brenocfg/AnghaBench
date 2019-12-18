#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpumask {int dummy; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_IPI_mask ) (struct cpumask const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* send_IPI_allbutself ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_FUNCTION_VECTOR ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  cpu_callout_mask ; 
 struct cpumask const* cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,struct cpumask const*) ; 
 scalar_t__ cpumask_equal (struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (struct cpumask const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct cpumask const*,int /*<<< orphan*/ ) ; 

void native_send_call_func_ipi(const struct cpumask *mask)
{
	cpumask_var_t allbutself;

	if (!alloc_cpumask_var(&allbutself, GFP_ATOMIC)) {
		apic->send_IPI_mask(mask, CALL_FUNCTION_VECTOR);
		return;
	}

	cpumask_copy(allbutself, cpu_online_mask);
	cpumask_clear_cpu(smp_processor_id(), allbutself);

	if (cpumask_equal(mask, allbutself) &&
	    cpumask_equal(cpu_online_mask, cpu_callout_mask))
		apic->send_IPI_allbutself(CALL_FUNCTION_VECTOR);
	else
		apic->send_IPI_mask(mask, CALL_FUNCTION_VECTOR);

	free_cpumask_var(allbutself);
}