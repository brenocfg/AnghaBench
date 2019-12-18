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

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  NR_IRQS_LEGACY ; 
 int arch_enable_uv_irq (char*,int,int,int,unsigned long,int) ; 
 int create_irq_nr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_irq (int) ; 
 int /*<<< orphan*/  uv_blade_to_memory_nid (int) ; 
 int /*<<< orphan*/  uv_set_irq_2_mmr_info (int,unsigned long,int) ; 

int uv_setup_irq(char *irq_name, int cpu, int mmr_blade,
		 unsigned long mmr_offset, int limit)
{
	int irq, ret;

	irq = create_irq_nr(NR_IRQS_LEGACY, uv_blade_to_memory_nid(mmr_blade));

	if (irq <= 0)
		return -EBUSY;

	ret = arch_enable_uv_irq(irq_name, irq, cpu, mmr_blade, mmr_offset,
		limit);
	if (ret == irq)
		uv_set_irq_2_mmr_info(irq, mmr_offset, mmr_blade);
	else
		destroy_irq(irq);

	return ret;
}