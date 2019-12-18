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
typedef  int uint32_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ plx9080_iobase; scalar_t__ hpdi_iobase; void* rx_fifo_size; void* tx_fifo_size; } ;

/* Variables and functions */
 scalar_t__ BOARD_CONTROL_REG ; 
 int BOARD_RESET_BIT ; 
 int ICS_AERR ; 
 int ICS_DMA0_E ; 
 int ICS_LIE ; 
 int ICS_PAIE ; 
 int ICS_PERR ; 
 int ICS_PIE ; 
 int ICS_PLIE ; 
 scalar_t__ INTERRUPT_CONTROL_REG ; 
 scalar_t__ PLX_INTRCS_REG ; 
 scalar_t__ RX_FIFO_SIZE_REG ; 
 scalar_t__ RX_PROG_ALMOST_REG ; 
 scalar_t__ TX_FIFO_SIZE_REG ; 
 scalar_t__ TX_PROG_ALMOST_REG ; 
 int almost_empty_bits (int) ; 
 int almost_full_bits (int) ; 
 void* fifo_size (int /*<<< orphan*/ ) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int init_hpdi(struct comedi_device *dev)
{
	uint32_t plx_intcsr_bits;

	writel(BOARD_RESET_BIT, priv(dev)->hpdi_iobase + BOARD_CONTROL_REG);
	udelay(10);

	writel(almost_empty_bits(32) | almost_full_bits(32),
	       priv(dev)->hpdi_iobase + RX_PROG_ALMOST_REG);
	writel(almost_empty_bits(32) | almost_full_bits(32),
	       priv(dev)->hpdi_iobase + TX_PROG_ALMOST_REG);

	priv(dev)->tx_fifo_size = fifo_size(readl(priv(dev)->hpdi_iobase +
						  TX_FIFO_SIZE_REG));
	priv(dev)->rx_fifo_size = fifo_size(readl(priv(dev)->hpdi_iobase +
						  RX_FIFO_SIZE_REG));

	writel(0, priv(dev)->hpdi_iobase + INTERRUPT_CONTROL_REG);

	/*  enable interrupts */
	plx_intcsr_bits =
	    ICS_AERR | ICS_PERR | ICS_PIE | ICS_PLIE | ICS_PAIE | ICS_LIE |
	    ICS_DMA0_E;
	writel(plx_intcsr_bits, priv(dev)->plx9080_iobase + PLX_INTRCS_REG);

	return 0;
}