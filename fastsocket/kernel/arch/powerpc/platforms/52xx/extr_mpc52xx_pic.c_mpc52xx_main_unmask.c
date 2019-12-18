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
struct TYPE_4__ {int /*<<< orphan*/  main_mask; } ;
struct TYPE_3__ {int hwirq; } ;

/* Variables and functions */
 int MPC52xx_IRQ_L2_MASK ; 
 TYPE_2__* intr ; 
 int /*<<< orphan*/  io_be_clrbit (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* irq_map ; 

__attribute__((used)) static void mpc52xx_main_unmask(unsigned int virq)
{
	int irq;
	int l2irq;

	irq = irq_map[virq].hwirq;
	l2irq = irq & MPC52xx_IRQ_L2_MASK;

	io_be_clrbit(&intr->main_mask, 16 - l2irq);
}