#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  processor_info_t ;
typedef  int processor_flavor_t ;
typedef  TYPE_2__* processor_cpu_stat_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_5__ {int /*<<< orphan*/  instr_ex_cnt; int /*<<< orphan*/  data_ex_cnt; int /*<<< orphan*/  vfp_cnt; int /*<<< orphan*/  unaligned_cnt; int /*<<< orphan*/  undef_ex_cnt; int /*<<< orphan*/  timer_cnt; int /*<<< orphan*/  ipi_cnt; int /*<<< orphan*/  irq_ex_cnt; } ;
struct TYPE_7__ {TYPE_1__ cpu_stat; } ;
typedef  TYPE_3__ cpu_data_t ;
struct TYPE_8__ {TYPE_3__* cpu_data_vaddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  instr_ex_cnt; int /*<<< orphan*/  data_ex_cnt; int /*<<< orphan*/  vfp_shortv_cnt; int /*<<< orphan*/  vfp_cnt; int /*<<< orphan*/  unaligned_cnt; int /*<<< orphan*/  undef_ex_cnt; int /*<<< orphan*/  timer_cnt; int /*<<< orphan*/  ipi_cnt; int /*<<< orphan*/  irq_ex_cnt; } ;

/* Variables and functions */
 TYPE_4__* CpuDataEntries ; 
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
#define  PROCESSOR_CPU_STAT 128 
 unsigned int PROCESSOR_CPU_STAT_COUNT ; 

kern_return_t
cpu_info(processor_flavor_t flavor,
	 int slot_num,
	 processor_info_t info,
	 unsigned int *count)
{
	switch (flavor) {
	case PROCESSOR_CPU_STAT:
		{
			processor_cpu_stat_t cpu_stat;
			cpu_data_t     *cpu_data_ptr = CpuDataEntries[slot_num].cpu_data_vaddr;

			if (*count < PROCESSOR_CPU_STAT_COUNT)
				return (KERN_FAILURE);

			cpu_stat = (processor_cpu_stat_t) info;
			cpu_stat->irq_ex_cnt = cpu_data_ptr->cpu_stat.irq_ex_cnt;
			cpu_stat->ipi_cnt = cpu_data_ptr->cpu_stat.ipi_cnt;
			cpu_stat->timer_cnt = cpu_data_ptr->cpu_stat.timer_cnt;
			cpu_stat->undef_ex_cnt = cpu_data_ptr->cpu_stat.undef_ex_cnt;
			cpu_stat->unaligned_cnt = cpu_data_ptr->cpu_stat.unaligned_cnt;
			cpu_stat->vfp_cnt = cpu_data_ptr->cpu_stat.vfp_cnt;
			cpu_stat->vfp_shortv_cnt = 0;
			cpu_stat->data_ex_cnt = cpu_data_ptr->cpu_stat.data_ex_cnt;
			cpu_stat->instr_ex_cnt = cpu_data_ptr->cpu_stat.instr_ex_cnt;

			*count = PROCESSOR_CPU_STAT_COUNT;

			return (KERN_SUCCESS);
		}

	default:
		return (KERN_FAILURE);
	}
}