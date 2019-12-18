#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__* p_dev; } ;
typedef  TYPE_3__ btuart_info_t ;
struct TYPE_5__ {unsigned int BasePort1; } ;
struct TYPE_6__ {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
 unsigned int SPEED_MAX ; 
 scalar_t__ UART_DLL ; 
 scalar_t__ UART_DLM ; 
 scalar_t__ UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int UART_FCR_TRIGGER_1 ; 
 int UART_FCR_TRIGGER_14 ; 
 scalar_t__ UART_IER ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int UART_IER_THRI ; 
 scalar_t__ UART_LCR ; 
 int UART_LCR_DLAB ; 
 int UART_LCR_WLEN8 ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void btuart_change_speed(btuart_info_t *info, unsigned int speed)
{
	unsigned long flags;
	unsigned int iobase;
	int fcr;		/* FIFO control reg */
	int lcr;		/* Line control reg */
	int divisor;

	if (!info) {
		BT_ERR("Unknown device");
		return;
	}

	iobase = info->p_dev->io.BasePort1;

	spin_lock_irqsave(&(info->lock), flags);

	/* Turn off interrupts */
	outb(0, iobase + UART_IER);

	divisor = SPEED_MAX / speed;

	fcr = UART_FCR_ENABLE_FIFO | UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT;

	/* 
	 * Use trigger level 1 to avoid 3 ms. timeout delay at 9600 bps, and
	 * almost 1,7 ms at 19200 bps. At speeds above that we can just forget
	 * about this timeout since it will always be fast enough. 
	 */

	if (speed < 38400)
		fcr |= UART_FCR_TRIGGER_1;
	else
		fcr |= UART_FCR_TRIGGER_14;

	/* Bluetooth cards use 8N1 */
	lcr = UART_LCR_WLEN8;

	outb(UART_LCR_DLAB | lcr, iobase + UART_LCR);	/* Set DLAB */
	outb(divisor & 0xff, iobase + UART_DLL);	/* Set speed */
	outb(divisor >> 8, iobase + UART_DLM);
	outb(lcr, iobase + UART_LCR);	/* Set 8N1  */
	outb(fcr, iobase + UART_FCR);	/* Enable FIFO's */

	/* Turn on interrupts */
	outb(UART_IER_RLSI | UART_IER_RDI | UART_IER_THRI, iobase + UART_IER);

	spin_unlock_irqrestore(&(info->lock), flags);
}