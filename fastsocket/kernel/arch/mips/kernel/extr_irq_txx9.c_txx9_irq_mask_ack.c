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
struct TYPE_4__ {int /*<<< orphan*/  scr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 unsigned int TXX9_IRQ_BASE ; 
 int /*<<< orphan*/  TXx9_IRCR_EDGE (int /*<<< orphan*/ ) ; 
 unsigned int TXx9_IRSCR_EIClrE ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ *) ; 
 TYPE_2__* txx9_ircptr ; 
 int /*<<< orphan*/  txx9_irq_mask (unsigned int) ; 
 TYPE_1__* txx9irq ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void txx9_irq_mask_ack(unsigned int irq)
{
	unsigned int irq_nr = irq - TXX9_IRQ_BASE;

	txx9_irq_mask(irq);
	/* clear edge detection */
	if (unlikely(TXx9_IRCR_EDGE(txx9irq[irq_nr].mode)))
		__raw_writel(TXx9_IRSCR_EIClrE | irq_nr, &txx9_ircptr->scr);
}