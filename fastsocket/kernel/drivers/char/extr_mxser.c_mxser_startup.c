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
struct tty_struct {int /*<<< orphan*/  flags; struct mxser_port* driver_data; } ;
struct TYPE_4__ {int flags; unsigned char* xmit_buf; } ;
struct mxser_port {int MCR; int IER; int /*<<< orphan*/  slock; TYPE_2__ port; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; scalar_t__ ioaddr; TYPE_1__* board; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ chip_flag; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MOXA_MUST_FCR_GDA_MODE_ENABLE ; 
 int MOXA_MUST_IER_EGDAI ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 scalar_t__ UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 scalar_t__ UART_IER ; 
 int UART_IER_MSI ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 scalar_t__ UART_IIR ; 
 scalar_t__ UART_LCR ; 
 int UART_LCR_WLEN8 ; 
 scalar_t__ UART_LSR ; 
 scalar_t__ UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 scalar_t__ UART_MSR ; 
 scalar_t__ UART_RX ; 
 unsigned long __get_free_page (int /*<<< orphan*/ ) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  mxser_change_speed (struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mxser_startup(struct tty_struct *tty)
{
	struct mxser_port *info = tty->driver_data;
	unsigned long page;
	unsigned long flags;

	page = __get_free_page(GFP_KERNEL);
	if (!page)
		return -ENOMEM;

	spin_lock_irqsave(&info->slock, flags);

	if (info->port.flags & ASYNC_INITIALIZED) {
		free_page(page);
		spin_unlock_irqrestore(&info->slock, flags);
		return 0;
	}

	if (!info->ioaddr || !info->type) {
		set_bit(TTY_IO_ERROR, &tty->flags);
		free_page(page);
		spin_unlock_irqrestore(&info->slock, flags);
		return 0;
	}
	if (info->port.xmit_buf)
		free_page(page);
	else
		info->port.xmit_buf = (unsigned char *) page;

	/*
	 * Clear the FIFO buffers and disable them
	 * (they will be reenabled in mxser_change_speed())
	 */
	if (info->board->chip_flag)
		outb((UART_FCR_CLEAR_RCVR |
			UART_FCR_CLEAR_XMIT |
			MOXA_MUST_FCR_GDA_MODE_ENABLE), info->ioaddr + UART_FCR);
	else
		outb((UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT),
			info->ioaddr + UART_FCR);

	/*
	 * At this point there's no way the LSR could still be 0xFF;
	 * if it is, then bail out, because there's likely no UART
	 * here.
	 */
	if (inb(info->ioaddr + UART_LSR) == 0xff) {
		spin_unlock_irqrestore(&info->slock, flags);
		if (capable(CAP_SYS_ADMIN)) {
			if (tty)
				set_bit(TTY_IO_ERROR, &tty->flags);
			return 0;
		} else
			return -ENODEV;
	}

	/*
	 * Clear the interrupt registers.
	 */
	(void) inb(info->ioaddr + UART_LSR);
	(void) inb(info->ioaddr + UART_RX);
	(void) inb(info->ioaddr + UART_IIR);
	(void) inb(info->ioaddr + UART_MSR);

	/*
	 * Now, initialize the UART
	 */
	outb(UART_LCR_WLEN8, info->ioaddr + UART_LCR);	/* reset DLAB */
	info->MCR = UART_MCR_DTR | UART_MCR_RTS;
	outb(info->MCR, info->ioaddr + UART_MCR);

	/*
	 * Finally, enable interrupts
	 */
	info->IER = UART_IER_MSI | UART_IER_RLSI | UART_IER_RDI;

	if (info->board->chip_flag)
		info->IER |= MOXA_MUST_IER_EGDAI;
	outb(info->IER, info->ioaddr + UART_IER);	/* enable interrupts */

	/*
	 * And clear the interrupt registers again for luck.
	 */
	(void) inb(info->ioaddr + UART_LSR);
	(void) inb(info->ioaddr + UART_RX);
	(void) inb(info->ioaddr + UART_IIR);
	(void) inb(info->ioaddr + UART_MSR);

	clear_bit(TTY_IO_ERROR, &tty->flags);
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;

	/*
	 * and set the speed of the serial port
	 */
	mxser_change_speed(tty, NULL);
	info->port.flags |= ASYNC_INITIALIZED;
	spin_unlock_irqrestore(&info->slock, flags);

	return 0;
}