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
struct sclp_cpu_info {int combined; int configured; TYPE_1__* cpu; scalar_t__ has_cpu_type; } ;
typedef  int /*<<< orphan*/  cpumask_t ;
struct TYPE_2__ {scalar_t__ type; int address; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_STATE_CONFIGURED ; 
 int /*<<< orphan*/  CPU_STATE_STANDBY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  POLARIZATION_UNKNWN ; 
 int* __cpu_logical_map ; 
 scalar_t__ cpu_known (int) ; 
 int /*<<< orphan*/  cpu_present_map ; 
 int /*<<< orphan*/  cpu_set (int,int /*<<< orphan*/ ) ; 
 int cpumask_first (int /*<<< orphan*/ *) ; 
 int cpumask_next (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct sclp_cpu_info*) ; 
 struct sclp_cpu_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 int sclp_get_cpu_info (struct sclp_cpu_info*) ; 
 int /*<<< orphan*/ * smp_cpu_polarization ; 
 int /*<<< orphan*/ * smp_cpu_state ; 
 scalar_t__ smp_cpu_type ; 

__attribute__((used)) static int smp_rescan_cpus_sclp(cpumask_t avail)
{
	struct sclp_cpu_info *info;
	int cpu_id, logical_cpu, cpu;
	int rc;

	logical_cpu = cpumask_first(&avail);
	if (logical_cpu >= nr_cpu_ids)
		return 0;
	info = kmalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;
	rc = sclp_get_cpu_info(info);
	if (rc)
		goto out;
	for (cpu = 0; cpu < info->combined; cpu++) {
		if (info->has_cpu_type && info->cpu[cpu].type != smp_cpu_type)
			continue;
		cpu_id = info->cpu[cpu].address;
		if (cpu_known(cpu_id))
			continue;
		__cpu_logical_map[logical_cpu] = cpu_id;
		smp_cpu_polarization[logical_cpu] = POLARIZATION_UNKNWN;
		cpu_set(logical_cpu, cpu_present_map);
		if (cpu >= info->configured)
			smp_cpu_state[logical_cpu] = CPU_STATE_STANDBY;
		else
			smp_cpu_state[logical_cpu] = CPU_STATE_CONFIGURED;
		logical_cpu = cpumask_next(logical_cpu, &avail);
		if (logical_cpu >= nr_cpu_ids)
			break;
	}
out:
	kfree(info);
	return rc;
}