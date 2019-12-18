#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int isr0; int isr1; } ;
union sab82532_irq_status {TYPE_8__ sreg; } ;
struct TYPE_17__ {int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  parity; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct TYPE_19__ {scalar_t__ line; int read_status_mask; int ignore_status_mask; TYPE_7__ icount; TYPE_6__* cons; TYPE_2__* state; } ;
struct uart_sunsab_port {TYPE_9__ port; TYPE_5__* regs; } ;
struct tty_struct {int dummy; } ;
struct TYPE_16__ {scalar_t__ index; } ;
struct TYPE_14__ {int /*<<< orphan*/  cmdr; } ;
struct TYPE_13__ {int /*<<< orphan*/ * rfifo; int /*<<< orphan*/  rbcl; } ;
struct TYPE_15__ {TYPE_4__ w; TYPE_3__ r; } ;
struct TYPE_11__ {struct tty_struct* tty; } ;
struct TYPE_12__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB82532_CMDR_RFRD ; 
 int /*<<< orphan*/  SAB82532_CMDR_RMC ; 
 int SAB82532_ISR0_FERR ; 
 int SAB82532_ISR0_PERR ; 
 int SAB82532_ISR0_RFO ; 
 int SAB82532_ISR0_RPF ; 
 int SAB82532_ISR0_TCD ; 
 int SAB82532_ISR0_TIME ; 
 int SAB82532_ISR1_BRK ; 
 int SAB82532_RECV_FIFO_SIZE ; 
 unsigned char TTY_BREAK ; 
 unsigned char TTY_FRAME ; 
 unsigned char TTY_NORMAL ; 
 unsigned char TTY_OVERRUN ; 
 unsigned char TTY_PARITY ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun_do_break () ; 
 int /*<<< orphan*/  sunsab_cec_wait (struct uart_sunsab_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,unsigned char) ; 
 scalar_t__ uart_handle_break (TYPE_9__*) ; 
 scalar_t__ uart_handle_sysrq_char (TYPE_9__*,unsigned char) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct tty_struct *
receive_chars(struct uart_sunsab_port *up,
	      union sab82532_irq_status *stat)
{
	struct tty_struct *tty = NULL;
	unsigned char buf[32];
	int saw_console_brk = 0;
	int free_fifo = 0;
	int count = 0;
	int i;

	if (up->port.state != NULL)		/* Unopened serial console */
		tty = up->port.state->port.tty;

	/* Read number of BYTES (Character + Status) available. */
	if (stat->sreg.isr0 & SAB82532_ISR0_RPF) {
		count = SAB82532_RECV_FIFO_SIZE;
		free_fifo++;
	}

	if (stat->sreg.isr0 & SAB82532_ISR0_TCD) {
		count = readb(&up->regs->r.rbcl) & (SAB82532_RECV_FIFO_SIZE - 1);
		free_fifo++;
	}

	/* Issue a FIFO read command in case we where idle. */
	if (stat->sreg.isr0 & SAB82532_ISR0_TIME) {
		sunsab_cec_wait(up);
		writeb(SAB82532_CMDR_RFRD, &up->regs->w.cmdr);
		return tty;
	}

	if (stat->sreg.isr0 & SAB82532_ISR0_RFO)
		free_fifo++;

	/* Read the FIFO. */
	for (i = 0; i < count; i++)
		buf[i] = readb(&up->regs->r.rfifo[i]);

	/* Issue Receive Message Complete command. */
	if (free_fifo) {
		sunsab_cec_wait(up);
		writeb(SAB82532_CMDR_RMC, &up->regs->w.cmdr);
	}

	/* Count may be zero for BRK, so we check for it here */
	if ((stat->sreg.isr1 & SAB82532_ISR1_BRK) &&
	    (up->port.line == up->port.cons->index))
		saw_console_brk = 1;

	for (i = 0; i < count; i++) {
		unsigned char ch = buf[i], flag;

		if (tty == NULL) {
			uart_handle_sysrq_char(&up->port, ch);
			continue;
		}

		flag = TTY_NORMAL;
		up->port.icount.rx++;

		if (unlikely(stat->sreg.isr0 & (SAB82532_ISR0_PERR |
						SAB82532_ISR0_FERR |
						SAB82532_ISR0_RFO)) ||
		    unlikely(stat->sreg.isr1 & SAB82532_ISR1_BRK)) {
			/*
			 * For statistics only
			 */
			if (stat->sreg.isr1 & SAB82532_ISR1_BRK) {
				stat->sreg.isr0 &= ~(SAB82532_ISR0_PERR |
						     SAB82532_ISR0_FERR);
				up->port.icount.brk++;
				/*
				 * We do the SysRQ and SAK checking
				 * here because otherwise the break
				 * may get masked by ignore_status_mask
				 * or read_status_mask.
				 */
				if (uart_handle_break(&up->port))
					continue;
			} else if (stat->sreg.isr0 & SAB82532_ISR0_PERR)
				up->port.icount.parity++;
			else if (stat->sreg.isr0 & SAB82532_ISR0_FERR)
				up->port.icount.frame++;
			if (stat->sreg.isr0 & SAB82532_ISR0_RFO)
				up->port.icount.overrun++;

			/*
			 * Mask off conditions which should be ingored.
			 */
			stat->sreg.isr0 &= (up->port.read_status_mask & 0xff);
			stat->sreg.isr1 &= ((up->port.read_status_mask >> 8) & 0xff);

			if (stat->sreg.isr1 & SAB82532_ISR1_BRK) {
				flag = TTY_BREAK;
			} else if (stat->sreg.isr0 & SAB82532_ISR0_PERR)
				flag = TTY_PARITY;
			else if (stat->sreg.isr0 & SAB82532_ISR0_FERR)
				flag = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(&up->port, ch))
			continue;

		if ((stat->sreg.isr0 & (up->port.ignore_status_mask & 0xff)) == 0 &&
		    (stat->sreg.isr1 & ((up->port.ignore_status_mask >> 8) & 0xff)) == 0)
			tty_insert_flip_char(tty, ch, flag);
		if (stat->sreg.isr0 & SAB82532_ISR0_RFO)
			tty_insert_flip_char(tty, 0, TTY_OVERRUN);
	}

	if (saw_console_brk)
		sun_do_break();

	return tty;
}