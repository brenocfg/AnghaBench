#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct et131x_adapter {TYPE_2__* pdev; TYPE_4__* regs; } ;
struct TYPE_7__ {int halt_status; } ;
struct TYPE_12__ {void* value; TYPE_1__ bits; } ;
struct TYPE_9__ {int /*<<< orphan*/  value; } ;
struct TYPE_11__ {TYPE_3__ csr; } ;
struct TYPE_10__ {TYPE_5__ rxdma; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_6__ RXDMA_CSR_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,void*) ; 
 void* readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void et131x_rx_dma_disable(struct et131x_adapter *etdev)
{
	RXDMA_CSR_t csr;

	/* Setup the receive dma configuration register */
	writel(0x00002001, &etdev->regs->rxdma.csr.value);
	csr.value = readl(&etdev->regs->rxdma.csr.value);
	if (csr.bits.halt_status != 1) {
		udelay(5);
		csr.value = readl(&etdev->regs->rxdma.csr.value);
		if (csr.bits.halt_status != 1)
			dev_err(&etdev->pdev->dev,
				"RX Dma failed to enter halt state. CSR 0x%08x\n",
				csr.value);
	}
}