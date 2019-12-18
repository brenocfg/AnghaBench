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
typedef  int u8 ;
struct irq_desc {TYPE_1__* chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* ack ) (unsigned int) ;int /*<<< orphan*/  (* mask ) (unsigned int) ;} ;

/* Variables and functions */
 int IRQ_BASE ; 
 scalar_t__ S6_GPIO_BANK (int /*<<< orphan*/ ) ; 
 scalar_t__ S6_GPIO_MIS ; 
 scalar_t__ S6_REG_GPIO ; 
 int ffs (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int* get_irq_desc_data (struct irq_desc*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (unsigned int) ; 

__attribute__((used)) static void demux_irqs(unsigned int irq, struct irq_desc *desc)
{
	u8 *mask = get_irq_desc_data(desc);
	u8 pending;
	int cirq;

	desc->chip->mask(irq);
	desc->chip->ack(irq);
	pending = readb(S6_REG_GPIO + S6_GPIO_BANK(0) + S6_GPIO_MIS) & *mask;
	cirq = IRQ_BASE - 1;
	while (pending) {
		int n = ffs(pending);
		cirq += n;
		pending >>= n;
		generic_handle_irq(cirq);
	}
	desc->chip->unmask(irq);
}