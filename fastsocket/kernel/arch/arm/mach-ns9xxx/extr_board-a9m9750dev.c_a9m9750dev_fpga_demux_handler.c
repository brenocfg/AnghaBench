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
struct TYPE_2__ {int /*<<< orphan*/  (* unmask ) (unsigned int) ;int /*<<< orphan*/  (* mask_ack ) (unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FPGA_IRQ (int) ; 
 int /*<<< orphan*/  FPGA_ISR ; 
 int __raw_readb (int /*<<< orphan*/ ) ; 
 int fls (int) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 

__attribute__((used)) static void a9m9750dev_fpga_demux_handler(unsigned int irq,
		struct irq_desc *desc)
{
	u8 stat = __raw_readb(FPGA_ISR);

	desc->chip->mask_ack(irq);

	while (stat != 0) {
		int irqno = fls(stat) - 1;

		stat &= ~(1 << irqno);

		generic_handle_irq(FPGA_IRQ(irqno));
	}

	desc->chip->unmask(irq);
}