#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct unw_frame_info {scalar_t__ sw; } ;
typedef  scalar_t__ __u64 ;
struct TYPE_3__ {scalar_t__ ksp; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  crash_save_this_cpu () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  ia64_set_psr_mc () ; 
 int /*<<< orphan*/  kdump_cpu_frozen ; 
 int* kdump_status ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  mb () ; 
 int smp_processor_id () ; 

void
kdump_cpu_freeze(struct unw_frame_info *info, void *arg)
{
	int cpuid;

	local_irq_disable();
	cpuid = smp_processor_id();
	crash_save_this_cpu();
	current->thread.ksp = (__u64)info->sw - 16;

	ia64_set_psr_mc();	/* mask MCA/INIT and stop reentrance */

	atomic_inc(&kdump_cpu_frozen);
	kdump_status[cpuid] = 1;
	mb();
	for (;;)
		cpu_relax();
}