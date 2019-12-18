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
struct TYPE_4__ {int /*<<< orphan*/  max_pfn; int /*<<< orphan*/  pfn_to_mfn_frame_list_list; } ;
struct TYPE_5__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__* HYPERVISOR_shared_info ; 
 int /*<<< orphan*/  p2m_top_mfn_list ; 
 int /*<<< orphan*/  virt_to_mfn (int /*<<< orphan*/ ) ; 
 TYPE_2__ xen_dummy_shared_info ; 
 int /*<<< orphan*/  xen_max_p2m_pfn ; 

void xen_setup_mfn_list_list(void)
{
	BUG_ON(HYPERVISOR_shared_info == &xen_dummy_shared_info);

	HYPERVISOR_shared_info->arch.pfn_to_mfn_frame_list_list =
		virt_to_mfn(p2m_top_mfn_list);
	HYPERVISOR_shared_info->arch.max_pfn = xen_max_p2m_pfn;
}