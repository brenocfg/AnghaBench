#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dtl_enable_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_FEATURE_SPLPAR ; 
 unsigned long __pa (TYPE_1__*) ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_1__* get_lppaca () ; 
 TYPE_1__* get_slb_shadow () ; 
 int /*<<< orphan*/  hard_smp_processor_id () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int unregister_dtl (int /*<<< orphan*/ ) ; 
 scalar_t__ unregister_slb_shadow (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unregister_vpa (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void pseries_kexec_cpu_down(int crash_shutdown, int secondary)
{
	/* Don't risk a hypervisor call if we're crashing */
	if (firmware_has_feature(FW_FEATURE_SPLPAR) && !crash_shutdown) {
		unsigned long addr;
		int ret;

		if (get_lppaca()->dtl_enable_mask) {
			ret = unregister_dtl(hard_smp_processor_id());
			if (ret) {
				pr_err("WARNING: DTL deregistration for cpu "
				       "%d (hw %d) failed with %d\n",
				       smp_processor_id(),
				       hard_smp_processor_id(), ret);
			}
		}

		addr = __pa(get_slb_shadow());
		if (unregister_slb_shadow(hard_smp_processor_id(), addr))
			printk("SLB shadow buffer deregistration of "
			       "cpu %u (hw_cpu_id %d) failed\n",
			       smp_processor_id(),
			       hard_smp_processor_id());

		addr = __pa(get_lppaca());
		if (unregister_vpa(hard_smp_processor_id(), addr)) {
			printk("VPA deregistration of cpu %u (hw_cpu_id %d) "
					"failed\n", smp_processor_id(),
					hard_smp_processor_id());
		}
	}
}