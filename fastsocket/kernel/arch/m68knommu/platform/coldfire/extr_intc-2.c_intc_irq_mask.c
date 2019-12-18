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

/* Variables and functions */
 scalar_t__ MCFICM_INTC0 ; 
 scalar_t__ MCFICM_INTC1 ; 
 scalar_t__ MCFINTC_IMRH ; 
 scalar_t__ MCFINTC_IMRL ; 
 unsigned int MCFINT_VECBASE ; 
 unsigned long MCF_IPSBAR ; 
 int __raw_readl (unsigned long) ; 
 int /*<<< orphan*/  __raw_writel (int,unsigned long) ; 

__attribute__((used)) static void intc_irq_mask(unsigned int irq)
{
	if ((irq >= MCFINT_VECBASE) && (irq <= MCFINT_VECBASE + 128)) {
		unsigned long imraddr;
		u32 val, imrbit;

		irq -= MCFINT_VECBASE;
		imraddr = MCF_IPSBAR;
		imraddr += (irq & 0x40) ? MCFICM_INTC1 : MCFICM_INTC0;
		imraddr += (irq & 0x20) ? MCFINTC_IMRH : MCFINTC_IMRL;
		imrbit = 0x1 << (irq & 0x1f);

		val = __raw_readl(imraddr);
		__raw_writel(val | imrbit, imraddr);
	}
}