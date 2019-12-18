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
struct ucode_cpu_info {scalar_t__ mc; scalar_t__ valid; } ;
struct sys_device {int id; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* apply_microcode ) (int) ;} ;

/* Variables and functions */
 TYPE_1__* microcode_ops ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 struct ucode_cpu_info* ucode_cpu_info ; 

__attribute__((used)) static int mc_sysdev_resume(struct sys_device *dev)
{
	int cpu = dev->id;
	struct ucode_cpu_info *uci = ucode_cpu_info + cpu;

	if (cpu != smp_processor_id())
		return 0;

	if (uci->valid && uci->mc)
		microcode_ops->apply_microcode(cpu);

	return 0;
}