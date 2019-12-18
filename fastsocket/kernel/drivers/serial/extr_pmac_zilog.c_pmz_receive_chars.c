#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct TYPE_13__ {unsigned char read_status_mask; int ignore_status_mask; TYPE_3__ icount; int /*<<< orphan*/  lock; scalar_t__ sysrq; TYPE_2__* state; } ;
struct uart_pmac_port {unsigned char parity_mask; int flags; int* curregs; TYPE_5__* dev; TYPE_6__ port; } ;
struct tty_struct {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {TYPE_4__ ofdev; } ;
struct TYPE_8__ {struct tty_struct* tty; } ;
struct TYPE_9__ {TYPE_1__ port; } ;

/* Variables and functions */
 unsigned char BRK_ABRT ; 
 unsigned char CRC_ERR ; 
 int ERR_RES ; 
 int EXT_INT_ENAB ; 
 int HZ ; 
 unsigned char PAR_ERR ; 
 int PMACZILOG_FLAG_BREAK ; 
 size_t R0 ; 
 size_t R1 ; 
 int RxINT_MASK ; 
 unsigned char Rx_CH_AV ; 
 unsigned char Rx_OVR ; 
 unsigned char TTY_BREAK ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_OVERRUN ; 
 unsigned char TTY_PARITY ; 
 int TxINT_ENAB ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ZS_IS_OPEN (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  pmz_debug (char*) ; 
 unsigned char read_zsdata (struct uart_pmac_port*) ; 
 unsigned char read_zsreg (struct uart_pmac_port*,size_t) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,unsigned char) ; 
 scalar_t__ uart_handle_break (TYPE_6__*) ; 
 int uart_handle_sysrq_char (TYPE_6__*,unsigned char) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,size_t,int) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static struct tty_struct *pmz_receive_chars(struct uart_pmac_port *uap)
{
	struct tty_struct *tty = NULL;
	unsigned char ch, r1, drop, error, flag;
	int loops = 0;

	/* The interrupt can be enabled when the port isn't open, typically
	 * that happens when using one port is open and the other closed (stale
	 * interrupt) or when one port is used as a console.
	 */
	if (!ZS_IS_OPEN(uap)) {
		pmz_debug("pmz: draining input\n");
		/* Port is closed, drain input data */
		for (;;) {
			if ((++loops) > 1000)
				goto flood;
			(void)read_zsreg(uap, R1);
			write_zsreg(uap, R0, ERR_RES);
			(void)read_zsdata(uap);
			ch = read_zsreg(uap, R0);
			if (!(ch & Rx_CH_AV))
				break;
		}
		return NULL;
	}

	/* Sanity check, make sure the old bug is no longer happening */
	if (uap->port.state == NULL || uap->port.state->port.tty == NULL) {
		WARN_ON(1);
		(void)read_zsdata(uap);
		return NULL;
	}
	tty = uap->port.state->port.tty;

	while (1) {
		error = 0;
		drop = 0;

		r1 = read_zsreg(uap, R1);
		ch = read_zsdata(uap);

		if (r1 & (PAR_ERR | Rx_OVR | CRC_ERR)) {
			write_zsreg(uap, R0, ERR_RES);
			zssync(uap);
		}

		ch &= uap->parity_mask;
		if (ch == 0 && uap->flags & PMACZILOG_FLAG_BREAK) {
			uap->flags &= ~PMACZILOG_FLAG_BREAK;
		}

#if defined(CONFIG_MAGIC_SYSRQ) && defined(CONFIG_SERIAL_CORE_CONSOLE)
#ifdef USE_CTRL_O_SYSRQ
		/* Handle the SysRq ^O Hack */
		if (ch == '\x0f') {
			uap->port.sysrq = jiffies + HZ*5;
			goto next_char;
		}
#endif /* USE_CTRL_O_SYSRQ */
		if (uap->port.sysrq) {
			int swallow;
			spin_unlock(&uap->port.lock);
			swallow = uart_handle_sysrq_char(&uap->port, ch);
			spin_lock(&uap->port.lock);
			if (swallow)
				goto next_char;
 		}
#endif /* CONFIG_MAGIC_SYSRQ && CONFIG_SERIAL_CORE_CONSOLE */

		/* A real serial line, record the character and status.  */
		if (drop)
			goto next_char;

		flag = TTY_NORMAL;
		uap->port.icount.rx++;

		if (r1 & (PAR_ERR | Rx_OVR | CRC_ERR | BRK_ABRT)) {
			error = 1;
			if (r1 & BRK_ABRT) {
				pmz_debug("pmz: got break !\n");
				r1 &= ~(PAR_ERR | CRC_ERR);
				uap->port.icount.brk++;
				if (uart_handle_break(&uap->port))
					goto next_char;
			}
			else if (r1 & PAR_ERR)
				uap->port.icount.parity++;
			else if (r1 & CRC_ERR)
				uap->port.icount.frame++;
			if (r1 & Rx_OVR)
				uap->port.icount.overrun++;
			r1 &= uap->port.read_status_mask;
			if (r1 & BRK_ABRT)
				flag = TTY_BREAK;
			else if (r1 & PAR_ERR)
				flag = TTY_PARITY;
			else if (r1 & CRC_ERR)
				flag = TTY_FRAME;
		}

		if (uap->port.ignore_status_mask == 0xff ||
		    (r1 & uap->port.ignore_status_mask) == 0) {
		    	tty_insert_flip_char(tty, ch, flag);
		}
		if (r1 & Rx_OVR)
			tty_insert_flip_char(tty, 0, TTY_OVERRUN);
	next_char:
		/* We can get stuck in an infinite loop getting char 0 when the
		 * line is in a wrong HW state, we break that here.
		 * When that happens, I disable the receive side of the driver.
		 * Note that what I've been experiencing is a real irq loop where
		 * I'm getting flooded regardless of the actual port speed.
		 * Something stange is going on with the HW
		 */
		if ((++loops) > 1000)
			goto flood;
		ch = read_zsreg(uap, R0);
		if (!(ch & Rx_CH_AV))
			break;
	}

	return tty;
 flood:
	uap->curregs[R1] &= ~(EXT_INT_ENAB | TxINT_ENAB | RxINT_MASK);
	write_zsreg(uap, R1, uap->curregs[R1]);
	zssync(uap);
	dev_err(&uap->dev->ofdev.dev, "pmz: rx irq flood !\n");
	return tty;
}