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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct c2_dev {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  C2_HINT_MAKE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_BAR0_ADAPTER_HINT ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static inline void c2_activity(struct c2_dev *c2dev, u32 mq_index, u16 shared)
{
	/*
	 * First read the register to see if the FIFO is full, and if so,
	 * spin until it's not.  This isn't perfect -- there is no
	 * synchronization among the clients of the register, but in
	 * practice it prevents multiple CPU from hammering the bus
	 * with PCI RETRY. Note that when this does happen, the card
	 * cannot get on the bus and the card and system hang in a
	 * deadlock -- thus the need for this code. [TOT]
	 */
	while (readl(c2dev->regs + PCI_BAR0_ADAPTER_HINT) & 0x80000000)
		udelay(10);

	__raw_writel(C2_HINT_MAKE(mq_index, shared),
		     c2dev->regs + PCI_BAR0_ADAPTER_HINT);
}