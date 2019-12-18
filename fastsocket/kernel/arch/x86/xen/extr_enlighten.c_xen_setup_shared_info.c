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
struct shared_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  shared_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_PARAVIRT_BOOTMAP ; 
 struct shared_info* HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  XENFEAT_auto_translated_physmap ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 scalar_t__ fix_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_setup_mfn_list_list () ; 
 int /*<<< orphan*/  xen_setup_vcpu_info_placement () ; 
 TYPE_1__* xen_start_info ; 

void xen_setup_shared_info(void)
{
	if (!xen_feature(XENFEAT_auto_translated_physmap)) {
		set_fixmap(FIX_PARAVIRT_BOOTMAP,
			   xen_start_info->shared_info);

		HYPERVISOR_shared_info =
			(struct shared_info *)fix_to_virt(FIX_PARAVIRT_BOOTMAP);
	} else
		HYPERVISOR_shared_info =
			(struct shared_info *)__va(xen_start_info->shared_info);

#ifndef CONFIG_SMP
	/* In UP this is as good a place as any to set up shared info */
	xen_setup_vcpu_info_placement();
#endif

	xen_setup_mfn_list_list();
}