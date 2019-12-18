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
typedef  int u32 ;
struct ebus_dma_info {int flags; scalar_t__ regs; int /*<<< orphan*/  name; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 scalar_t__ EBDMA_CSR ; 
 int EBDMA_CSR_BURST_SZ_16 ; 
 int EBDMA_CSR_EN_CNT ; 
 int EBDMA_CSR_TCI_DIS ; 
 int EBUS_DMA_FLAG_TCI_DISABLE ; 
 int EBUS_DMA_FLAG_USE_EBDMA_HANDLER ; 
 int EINVAL ; 
 int /*<<< orphan*/  __ebus_dma_reset (struct ebus_dma_info*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int ebus_dma_register(struct ebus_dma_info *p)
{
	u32 csr;

	if (!p->regs)
		return -EINVAL;
	if (p->flags & ~(EBUS_DMA_FLAG_USE_EBDMA_HANDLER |
			 EBUS_DMA_FLAG_TCI_DISABLE))
		return -EINVAL;
	if ((p->flags & EBUS_DMA_FLAG_USE_EBDMA_HANDLER) && !p->callback)
		return -EINVAL;
	if (!strlen(p->name))
		return -EINVAL;

	__ebus_dma_reset(p, 1);

	csr = EBDMA_CSR_BURST_SZ_16 | EBDMA_CSR_EN_CNT;

	if (p->flags & EBUS_DMA_FLAG_TCI_DISABLE)
		csr |= EBDMA_CSR_TCI_DIS;

	writel(csr, p->regs + EBDMA_CSR);

	return 0;
}