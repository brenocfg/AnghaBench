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
struct op_system_config {int mmcr0; int /*<<< orphan*/  mmcr1; scalar_t__ enable_user; scalar_t__ enable_kernel; } ;
struct op_counter_config {scalar_t__ count; int /*<<< orphan*/  enabled; } ;
struct TYPE_2__ {int num_pmcs; } ;

/* Variables and functions */
 int PA6T_MMCR0_HYPEN ; 
 int PA6T_MMCR0_PREN ; 
 int PA6T_MMCR0_SUPEN ; 
 TYPE_1__* cur_cpu_spec ; 
 int mmcr0_val ; 
 int /*<<< orphan*/  mmcr1_val ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 scalar_t__* reset_value ; 

__attribute__((used)) static int pa6t_reg_setup(struct op_counter_config *ctr,
			   struct op_system_config *sys,
			   int num_ctrs)
{
	int pmc;

	/*
	 * adjust the mmcr0.en[0-5] and mmcr0.inten[0-5] values obtained from the
	 * event_mappings file by turning off the counters that the user doesn't
	 * care about
	 *
	 * setup user and kernel profiling
	 */
	for (pmc = 0; pmc < cur_cpu_spec->num_pmcs; pmc++)
		if (!ctr[pmc].enabled) {
			sys->mmcr0 &= ~(0x1UL << pmc);
			sys->mmcr0 &= ~(0x1UL << (pmc+12));
			pr_debug("turned off counter %u\n", pmc);
		}

	if (sys->enable_kernel)
		sys->mmcr0 |= PA6T_MMCR0_SUPEN | PA6T_MMCR0_HYPEN;
	else
		sys->mmcr0 &= ~(PA6T_MMCR0_SUPEN | PA6T_MMCR0_HYPEN);

	if (sys->enable_user)
		sys->mmcr0 |= PA6T_MMCR0_PREN;
	else
		sys->mmcr0 &= ~PA6T_MMCR0_PREN;

	/*
	 * The performance counter event settings are given in the mmcr0 and
	 * mmcr1 values passed from the user in the op_system_config
	 * structure (sys variable).
	 */
	mmcr0_val = sys->mmcr0;
	mmcr1_val = sys->mmcr1;
	pr_debug("mmcr0_val inited to %016lx\n", sys->mmcr0);
	pr_debug("mmcr1_val inited to %016lx\n", sys->mmcr1);

	for (pmc = 0; pmc < cur_cpu_spec->num_pmcs; pmc++) {
		/* counters are 40 bit. Move to cputable at some point? */
		reset_value[pmc] = (0x1UL << 39) - ctr[pmc].count;
		pr_debug("reset_value for pmc%u inited to 0x%llx\n",
				 pmc, reset_value[pmc]);
	}

	return 0;
}