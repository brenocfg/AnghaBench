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
typedef  int u8 ;
struct paravirt_patch_template {int /*<<< orphan*/  pv_lock_ops; int /*<<< orphan*/  pv_mmu_ops; int /*<<< orphan*/  pv_apic_ops; int /*<<< orphan*/  pv_irq_ops; int /*<<< orphan*/  pv_cpu_ops; int /*<<< orphan*/  pv_time_ops; int /*<<< orphan*/  pv_init_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  pv_apic_ops ; 
 int /*<<< orphan*/  pv_cpu_ops ; 
 int /*<<< orphan*/  pv_init_ops ; 
 int /*<<< orphan*/  pv_irq_ops ; 
 int /*<<< orphan*/  pv_lock_ops ; 
 int /*<<< orphan*/  pv_mmu_ops ; 
 int /*<<< orphan*/  pv_time_ops ; 

__attribute__((used)) static void *get_call_destination(u8 type)
{
	struct paravirt_patch_template tmpl = {
		.pv_init_ops = pv_init_ops,
		.pv_time_ops = pv_time_ops,
		.pv_cpu_ops = pv_cpu_ops,
		.pv_irq_ops = pv_irq_ops,
		.pv_apic_ops = pv_apic_ops,
		.pv_mmu_ops = pv_mmu_ops,
#ifdef CONFIG_PARAVIRT_SPINLOCKS
		.pv_lock_ops = pv_lock_ops,
#endif
	};
	return *((void **)&tmpl + type);
}