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
struct cpu_hw_events {int /*<<< orphan*/  shared_regs; } ;
struct TYPE_2__ {scalar_t__ extra_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct cpu_hw_events* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  allocate_shared_regs (int) ; 
 int /*<<< orphan*/  free_fake_cpuc (struct cpu_hw_events*) ; 
 struct cpu_hw_events* kzalloc (int,int /*<<< orphan*/ ) ; 
 int raw_smp_processor_id () ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static struct cpu_hw_events *allocate_fake_cpuc(void)
{
	struct cpu_hw_events *cpuc;
	int cpu = raw_smp_processor_id();

	cpuc = kzalloc(sizeof(*cpuc), GFP_KERNEL);
	if (!cpuc)
		return ERR_PTR(-ENOMEM);

	/* only needed, if we have extra_regs */
	if (x86_pmu.extra_regs) {
		cpuc->shared_regs = allocate_shared_regs(cpu);
		if (!cpuc->shared_regs)
			goto error;
	}
	return cpuc;
error:
	free_fake_cpuc(cpuc);
	return ERR_PTR(-ENOMEM);
}