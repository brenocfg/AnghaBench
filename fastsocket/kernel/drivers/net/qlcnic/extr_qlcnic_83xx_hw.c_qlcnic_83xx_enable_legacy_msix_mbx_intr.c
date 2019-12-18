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
typedef  scalar_t__ u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {scalar_t__ pci_base0; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_DEF_INT_MASK ; 
 scalar_t__ QLCRDX (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

inline void qlcnic_83xx_enable_legacy_msix_mbx_intr(struct qlcnic_adapter
						    *adapter)
{
	u32 mask;

	/* Mailbox in MSI-x mode and Legacy Interrupt share the same
	 * source register. We could be here before contexts are created
	 * and sds_ring->crb_intr_mask has not been initialized, calculate
	 * BAR offset for Interrupt Source Register
	 */
	mask = QLCRDX(adapter->ahw, QLCNIC_DEF_INT_MASK);
	writel(0, adapter->ahw->pci_base0 + mask);
}