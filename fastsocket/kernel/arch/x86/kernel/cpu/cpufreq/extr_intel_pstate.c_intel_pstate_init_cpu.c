#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct x86_cpu_id {scalar_t__ driver_data; } ;
struct pstate_adjust_policy {int dummy; } ;
struct TYPE_5__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_pstate; } ;
struct cpudata {unsigned int cpu; TYPE_2__ timer; TYPE_1__ pstate; struct pstate_adjust_policy* pstate_policy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  add_timer_on (TYPE_2__*,unsigned int) ; 
 struct cpudata** all_cpu_data ; 
 int /*<<< orphan*/  init_timer_deferrable (TYPE_2__*) ; 
 int /*<<< orphan*/  intel_pstate_busy_pid_reset (struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_cpu_ids ; 
 int /*<<< orphan*/  intel_pstate_get_cpu_pstates (struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_idle_pid_reset (struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_sample (struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_set_pstate (struct cpudata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pstate_timer_func ; 
 scalar_t__ jiffies ; 
 struct cpudata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int) ; 
 struct x86_cpu_id* x86_match_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pstate_init_cpu(unsigned int cpunum)
{

	const struct x86_cpu_id *id;
	struct cpudata *cpu;

	id = x86_match_cpu(intel_pstate_cpu_ids);
	if (!id)
		return -ENODEV;

	all_cpu_data[cpunum] = kzalloc(sizeof(struct cpudata), GFP_KERNEL);
	if (!all_cpu_data[cpunum])
		return -ENOMEM;

	cpu = all_cpu_data[cpunum];

	intel_pstate_get_cpu_pstates(cpu);

	cpu->cpu = cpunum;
	cpu->pstate_policy =
		(struct pstate_adjust_policy *)id->driver_data;
	init_timer_deferrable(&cpu->timer);
	cpu->timer.function = intel_pstate_timer_func;
	cpu->timer.data =
		(unsigned long)cpu;
	cpu->timer.expires = jiffies + HZ/100;
	intel_pstate_busy_pid_reset(cpu);
	intel_pstate_idle_pid_reset(cpu);
	intel_pstate_sample(cpu);
	intel_pstate_set_pstate(cpu, cpu->pstate.max_pstate);

	add_timer_on(&cpu->timer, cpunum);

	pr_info("Intel pstate controlling: cpu %d\n", cpunum);

	return 0;
}