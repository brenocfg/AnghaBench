#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct et131x_adapter {TYPE_2__* regs; scalar_t__ RegistryPhyLoopbk; } ;
struct TYPE_3__ {int /*<<< orphan*/  csr; } ;
struct TYPE_4__ {TYPE_1__ txdma; } ;

/* Variables and functions */
 int ET_TXDMA_CACHE_SHIFT ; 
 int ET_TXDMA_CSR_HALT ; 
 int ET_TXDMA_SNGL_EPKT ; 
 int PARM_DMA_CACHE_DEF ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

void et131x_tx_dma_enable(struct et131x_adapter *etdev)
{
	u32 csr = ET_TXDMA_SNGL_EPKT;
	if (etdev->RegistryPhyLoopbk)
		/* TxDMA is disabled for loopback operation. */
		csr |= ET_TXDMA_CSR_HALT;
	else
		/* Setup the transmit dma configuration register for normal
		 * operation
		 */
		csr |= PARM_DMA_CACHE_DEF << ET_TXDMA_CACHE_SHIFT;
	writel(csr, &etdev->regs->txdma.csr);
}