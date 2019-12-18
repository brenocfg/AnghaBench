#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct icst525_vco {int s; int v; int r; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_3__ {int /*<<< orphan*/  cpus_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CM_OSC ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cclk_params ; 
 int /*<<< orphan*/  cpumask_of_cpu (unsigned int) ; 
 TYPE_1__* current ; 
 unsigned int icst525_khz (int /*<<< orphan*/ *,struct icst525_vco) ; 
 scalar_t__ machine_is_cintegrator () ; 
 scalar_t__ machine_is_integrator () ; 
 int /*<<< orphan*/  set_cpus_allowed (TYPE_1__*,int /*<<< orphan*/ ) ; 
 unsigned int smp_processor_id () ; 

__attribute__((used)) static unsigned int integrator_get(unsigned int cpu)
{
	cpumask_t cpus_allowed;
	unsigned int current_freq;
	u_int cm_osc;
	struct icst525_vco vco;

	cpus_allowed = current->cpus_allowed;

	set_cpus_allowed(current, cpumask_of_cpu(cpu));
	BUG_ON(cpu != smp_processor_id());

	/* detect memory etc. */
	cm_osc = __raw_readl(CM_OSC);

	if (machine_is_integrator()) {
		vco.s = (cm_osc >> 8) & 7;
	} else if (machine_is_cintegrator()) {
		vco.s = 1;
	}
	vco.v = cm_osc & 255;
	vco.r = 22;

	current_freq = icst525_khz(&cclk_params, vco); /* current freq */

	set_cpus_allowed(current, cpus_allowed);

	return current_freq;
}