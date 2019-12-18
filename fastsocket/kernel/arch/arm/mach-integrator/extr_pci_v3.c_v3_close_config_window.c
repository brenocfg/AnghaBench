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
 int /*<<< orphan*/  PCI_BUS_PREMEM_START ; 
 scalar_t__ PHYS_PCI_MEM_BASE ; 
 scalar_t__ SZ_256M ; 
 int /*<<< orphan*/  V3_LB_BASE0 ; 
 int /*<<< orphan*/  V3_LB_BASE1 ; 
 int V3_LB_BASE_ADR_SIZE_256MB ; 
 int V3_LB_BASE_ENABLE ; 
 int V3_LB_BASE_PREFETCH ; 
 int /*<<< orphan*/  V3_LB_MAP1 ; 
 int V3_LB_MAP_TYPE_MEM_MULTIPLE ; 
 int v3_addr_to_lb_base (scalar_t__) ; 
 int v3_addr_to_lb_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v3_writel (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v3_writew (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void v3_close_config_window(void)
{
	/*
	 * Reassign base1 for use by prefetchable PCI memory
	 */
	v3_writel(V3_LB_BASE1, v3_addr_to_lb_base(PHYS_PCI_MEM_BASE + SZ_256M) |
			V3_LB_BASE_ADR_SIZE_256MB | V3_LB_BASE_PREFETCH |
			V3_LB_BASE_ENABLE);
	v3_writew(V3_LB_MAP1, v3_addr_to_lb_map(PCI_BUS_PREMEM_START) |
			V3_LB_MAP_TYPE_MEM_MULTIPLE);

	/*
	 * And shrink base0 back to a 256M window (NOTE: MAP0 already correct)
	 */
	v3_writel(V3_LB_BASE0, v3_addr_to_lb_base(PHYS_PCI_MEM_BASE) |
			V3_LB_BASE_ADR_SIZE_256MB | V3_LB_BASE_ENABLE);
}