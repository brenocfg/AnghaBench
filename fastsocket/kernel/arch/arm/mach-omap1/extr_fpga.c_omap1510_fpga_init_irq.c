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

/* Variables and functions */
 int /*<<< orphan*/  INNOVATOR_FPGA_IMR2 ; 
 int /*<<< orphan*/  IRQF_VALID ; 
 int /*<<< orphan*/  IRQ_TYPE_EDGE_RISING ; 
 int /*<<< orphan*/  OMAP1510_FPGA_IMR_HI ; 
 int /*<<< orphan*/  OMAP1510_FPGA_IMR_LO ; 
 int /*<<< orphan*/  OMAP1510_INT_FPGA ; 
 int OMAP1510_INT_FPGA_TS ; 
 int OMAP_FPGA_IRQ_BASE ; 
 int OMAP_FPGA_IRQ_END ; 
 int /*<<< orphan*/  __raw_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_request (int,char*) ; 
 int /*<<< orphan*/  gpio_to_irq (int) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  innovator_fpga_IRQ_demux ; 
 int /*<<< orphan*/  omap_fpga_irq ; 
 int /*<<< orphan*/  omap_fpga_irq_ack ; 
 int /*<<< orphan*/  set_irq_chained_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_chip (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_irq_flags (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_handler (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_irq_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap1510_fpga_init_irq(void)
{
	int i;

	__raw_writeb(0, OMAP1510_FPGA_IMR_LO);
	__raw_writeb(0, OMAP1510_FPGA_IMR_HI);
	__raw_writeb(0, INNOVATOR_FPGA_IMR2);

	for (i = OMAP_FPGA_IRQ_BASE; i < OMAP_FPGA_IRQ_END; i++) {

		if (i == OMAP1510_INT_FPGA_TS) {
			/*
			 * The touchscreen interrupt is level-sensitive, so
			 * we'll use the regular mask_ack routine for it.
			 */
			set_irq_chip(i, &omap_fpga_irq_ack);
		}
		else {
			/*
			 * All FPGA interrupts except the touchscreen are
			 * edge-sensitive, so we won't mask them.
			 */
			set_irq_chip(i, &omap_fpga_irq);
		}

		set_irq_handler(i, handle_edge_irq);
		set_irq_flags(i, IRQF_VALID);
	}

	/*
	 * The FPGA interrupt line is connected to GPIO13. Claim this pin for
	 * the ARM.
	 *
	 * NOTE: For general GPIO/MPUIO access and interrupts, please see
	 * gpio.[ch]
	 */
	gpio_request(13, "FPGA irq");
	gpio_direction_input(13);
	set_irq_type(gpio_to_irq(13), IRQ_TYPE_EDGE_RISING);
	set_irq_chained_handler(OMAP1510_INT_FPGA, innovator_fpga_IRQ_demux);
}