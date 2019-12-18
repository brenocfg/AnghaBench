#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; TYPE_2__* p_dev; int /*<<< orphan*/  hdev; } ;
typedef  TYPE_3__ btuart_info_t ;
struct TYPE_6__ {unsigned int BasePort1; } ;
struct TYPE_7__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ UART_IIR ; 
 int UART_IIR_ID ; 
#define  UART_IIR_RDI 130 
#define  UART_IIR_RLSI 129 
#define  UART_IIR_THRI 128 
 scalar_t__ UART_LSR ; 
 int UART_LSR_THRE ; 
 int /*<<< orphan*/  btuart_receive (TYPE_3__*) ; 
 int /*<<< orphan*/  btuart_write_wakeup (TYPE_3__*) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t btuart_interrupt(int irq, void *dev_inst)
{
	btuart_info_t *info = dev_inst;
	unsigned int iobase;
	int boguscount = 0;
	int iir, lsr;
	irqreturn_t r = IRQ_NONE;

	BUG_ON(!info->hdev);

	iobase = info->p_dev->io.BasePort1;

	spin_lock(&(info->lock));

	iir = inb(iobase + UART_IIR) & UART_IIR_ID;
	while (iir) {
		r = IRQ_HANDLED;

		/* Clear interrupt */
		lsr = inb(iobase + UART_LSR);

		switch (iir) {
		case UART_IIR_RLSI:
			BT_ERR("RLSI");
			break;
		case UART_IIR_RDI:
			/* Receive interrupt */
			btuart_receive(info);
			break;
		case UART_IIR_THRI:
			if (lsr & UART_LSR_THRE) {
				/* Transmitter ready for data */
				btuart_write_wakeup(info);
			}
			break;
		default:
			BT_ERR("Unhandled IIR=%#x", iir);
			break;
		}

		/* Make sure we don't stay here too long */
		if (boguscount++ > 100)
			break;

		iir = inb(iobase + UART_IIR) & UART_IIR_ID;

	}

	spin_unlock(&(info->lock));

	return r;
}