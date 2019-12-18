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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_hardware_context {scalar_t__ pci_func; } ;
struct TYPE_2__ {int /*<<< orphan*/  spurious_intr; } ;
struct qlcnic_adapter {int /*<<< orphan*/  tgt_status_reg; int /*<<< orphan*/  isr_int_vec; TYPE_1__ stats; struct qlcnic_hardware_context* ahw; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ QLC_83XX_INTX_FUNC (int /*<<< orphan*/ ) ; 
 int QLC_83XX_LEGACY_INTX_MAX_RETRY ; 
 scalar_t__ QLC_83XX_VALID_INTX_BIT30 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_83XX_VALID_INTX_BIT31 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

irqreturn_t qlcnic_83xx_clear_legacy_intr(struct qlcnic_adapter *adapter)
{
	u32 intr_val;
	struct qlcnic_hardware_context *ahw = adapter->ahw;
	int retries = 0;

	intr_val = readl(adapter->tgt_status_reg);

	if (!QLC_83XX_VALID_INTX_BIT31(intr_val))
		return IRQ_NONE;

	if (QLC_83XX_INTX_FUNC(intr_val) != adapter->ahw->pci_func) {
		adapter->stats.spurious_intr++;
		return IRQ_NONE;
	}
	/* The barrier is required to ensure writes to the registers */
	wmb();

	/* clear the interrupt trigger control register */
	writel(0, adapter->isr_int_vec);
	intr_val = readl(adapter->isr_int_vec);
	do {
		intr_val = readl(adapter->tgt_status_reg);
		if (QLC_83XX_INTX_FUNC(intr_val) != ahw->pci_func)
			break;
		retries++;
	} while (QLC_83XX_VALID_INTX_BIT30(intr_val) &&
		 (retries < QLC_83XX_LEGACY_INTX_MAX_RETRY));

	return IRQ_HANDLED;
}