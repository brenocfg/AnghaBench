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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMABRGCR ; 
 scalar_t__ DMABRGIRQ_A0TXF ; 
 scalar_t__ DMABRGIRQ_USBDMA ; 
 scalar_t__ DMABRGIRQ_USBDMAERR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int __ffs (unsigned long) ; 
 unsigned long ctrl_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outl (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmabrg_call_handler (scalar_t__) ; 

__attribute__((used)) static irqreturn_t dmabrg_irq(int irq, void *data)
{
	unsigned long dcr;
	unsigned int i;

	dcr = ctrl_inl(DMABRGCR);
	ctrl_outl(dcr & ~0x00ff0003, DMABRGCR);	/* ack all */
	dcr &= dcr >> 8;	/* ignore masked */

	/* USB stuff, get it out of the way first */
	if (dcr & 1)
		dmabrg_call_handler(DMABRGIRQ_USBDMA);
	if (dcr & 2)
		dmabrg_call_handler(DMABRGIRQ_USBDMAERR);

	/* Audio */
	dcr >>= 16;
	while (dcr) {
		i = __ffs(dcr);
		dcr &= dcr - 1;
		dmabrg_call_handler(i + DMABRGIRQ_A0TXF);
	}
	return IRQ_HANDLED;
}