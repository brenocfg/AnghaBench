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
 int /*<<< orphan*/  SYS_IC (int) ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int irq2prio (unsigned int) ; 

__attribute__((used)) static void ns9xxx_mask_irq(unsigned int irq)
{
	/* XXX: better use cpp symbols */
	int prio = irq2prio(irq);
	u32 ic = __raw_readl(SYS_IC(prio / 4));
	ic &= ~(1 << (7 + 8 * (3 - (prio & 3))));
	__raw_writel(ic, SYS_IC(prio / 4));
}