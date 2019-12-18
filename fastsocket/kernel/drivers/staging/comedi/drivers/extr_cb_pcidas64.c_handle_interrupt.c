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
struct comedi_device {scalar_t__ attached; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ plx9080_iobase; scalar_t__ main_iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_PRINT (char*,...) ; 
 scalar_t__ HW_STATUS_REG ; 
 int ICS_LDIA ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ PLX_DBR_OUT_REG ; 
 scalar_t__ PLX_INTRCS_REG ; 
 int /*<<< orphan*/  handle_ai_interrupt (struct comedi_device*,unsigned short,int) ; 
 int /*<<< orphan*/  handle_ao_interrupt (struct comedi_device*,unsigned short,int) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int readl (scalar_t__) ; 
 unsigned short readw (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t handle_interrupt(int irq, void *d)
{
	struct comedi_device *dev = d;
	unsigned short status;
	uint32_t plx_status;
	uint32_t plx_bits;

	plx_status = readl(priv(dev)->plx9080_iobase + PLX_INTRCS_REG);
	status = readw(priv(dev)->main_iobase + HW_STATUS_REG);

	DEBUG_PRINT("cb_pcidas64: hw status 0x%x ", status);
	DEBUG_PRINT("plx status 0x%x\n", plx_status);

	/* an interrupt before all the postconfig stuff gets done could
	 * cause a NULL dereference if we continue through the
	 * interrupt handler */
	if (dev->attached == 0) {
		DEBUG_PRINT("cb_pcidas64: premature interrupt, ignoring",
			    status);
		return IRQ_HANDLED;
	}
	handle_ai_interrupt(dev, status, plx_status);
	handle_ao_interrupt(dev, status, plx_status);

	/*  clear possible plx9080 interrupt sources */
	if (plx_status & ICS_LDIA) {	/*  clear local doorbell interrupt */
		plx_bits = readl(priv(dev)->plx9080_iobase + PLX_DBR_OUT_REG);
		writel(plx_bits, priv(dev)->plx9080_iobase + PLX_DBR_OUT_REG);
		DEBUG_PRINT(" cleared local doorbell bits 0x%x\n", plx_bits);
	}

	DEBUG_PRINT("exiting handler\n");

	return IRQ_HANDLED;
}