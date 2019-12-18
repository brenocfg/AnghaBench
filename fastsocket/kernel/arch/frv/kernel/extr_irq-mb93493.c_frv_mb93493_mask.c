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
typedef  int uint32_t ;

/* Variables and functions */
 unsigned int IRQ_BASE_MB93493 ; 
 int IRQ_ROUTING ; 
 void* __addr_MB93493_IQSR (int) ; 
 int readl (void volatile*) ; 
 int /*<<< orphan*/  writel (int,void volatile*) ; 

__attribute__((used)) static void frv_mb93493_mask(unsigned int irq)
{
	uint32_t iqsr;
	volatile void *piqsr;

	if (IRQ_ROUTING & (1 << (irq - IRQ_BASE_MB93493)))
		piqsr = __addr_MB93493_IQSR(1);
	else
		piqsr = __addr_MB93493_IQSR(0);

	iqsr = readl(piqsr);
	iqsr &= ~(1 << (irq - IRQ_BASE_MB93493 + 16));
	writel(iqsr, piqsr);
}