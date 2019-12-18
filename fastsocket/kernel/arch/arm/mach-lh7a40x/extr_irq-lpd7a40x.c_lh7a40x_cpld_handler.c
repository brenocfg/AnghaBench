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
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* ack ) (unsigned int) ;} ;

/* Variables and functions */
 unsigned int CPLD_INTERRUPTS ; 
 int /*<<< orphan*/  IRQ_LPD7A400_TS ; 
 int /*<<< orphan*/  IRQ_LPD7A40X_ETH_INT ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 

__attribute__((used)) static void lh7a40x_cpld_handler (unsigned int irq, struct irq_desc *desc)
{
	unsigned int mask = CPLD_INTERRUPTS;

	desc->chip->ack (irq);

	if ((mask & 0x1) == 0)	/* WLAN */
		generic_handle_irq(IRQ_LPD7A40X_ETH_INT);

	if ((mask & 0x2) == 0)	/* Touch */
		generic_handle_irq(IRQ_LPD7A400_TS);

	desc->chip->unmask (irq); /* Level-triggered need this */
}