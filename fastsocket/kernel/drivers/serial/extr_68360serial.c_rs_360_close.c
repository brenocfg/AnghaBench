#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int count; int closing; int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct smc_regs {int /*<<< orphan*/  smc_smcmr; int /*<<< orphan*/  smc_smcm; } ;
struct serial_state {int count; int smc_scc_num; } ;
struct TYPE_8__ {int /*<<< orphan*/  low; } ;
struct TYPE_9__ {TYPE_1__ w; } ;
struct scc_regs {TYPE_2__ scc_gsmr; int /*<<< orphan*/  scc_sccm; } ;
struct file {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * tty; } ;
struct TYPE_11__ {int flags; scalar_t__ closing_wait; int /*<<< orphan*/  close_wait; int /*<<< orphan*/  open_wait; scalar_t__ close_delay; scalar_t__ blocked_open; TYPE_3__ port; scalar_t__ event; int /*<<< orphan*/  timeout; struct serial_state* state; int /*<<< orphan*/  read_status_mask; int /*<<< orphan*/  line; } ;
typedef  TYPE_4__ ser_info_t ;
struct TYPE_12__ {struct smc_regs* smc_regs; struct scc_regs* scc_regs; } ;

/* Variables and functions */
 int ASYNC_CLOSING ; 
 scalar_t__ ASYNC_CLOSING_WAIT_NONE ; 
 int ASYNC_INITIALIZED ; 
 int ASYNC_NORMAL_ACTIVE ; 
 int /*<<< orphan*/  BD_SC_EMPTY ; 
 int /*<<< orphan*/  DBG_CNT (char*) ; 
 int NUM_IS_SCC ; 
 int PORT_NUM (int) ; 
 int /*<<< orphan*/  SCC_GSMRL_ENR ; 
 int /*<<< orphan*/  SMCMR_REN ; 
 int /*<<< orphan*/  SMCM_RX ; 
 int /*<<< orphan*/  UART_SCCM_RX ; 
 int /*<<< orphan*/  jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  msleep_interruptible (int /*<<< orphan*/ ) ; 
 TYPE_7__* pquicc ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 
 int /*<<< orphan*/  rs_360_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  rs_360_wait_until_sent (struct tty_struct*,int /*<<< orphan*/ ) ; 
 scalar_t__ serial_paranoia_check (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown (TYPE_4__*) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 int /*<<< orphan*/  tty_ldisc_flush (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_wait_until_sent (struct tty_struct*,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rs_360_close(struct tty_struct *tty, struct file * filp)
{
	ser_info_t *info = (ser_info_t *)tty->driver_data;
	/* struct async_state *state; */
	struct serial_state *state;
	unsigned long	flags;
	int		idx;
	volatile struct smc_regs	*smcp;
	volatile struct scc_regs	*sccp;

	if (!info || serial_paranoia_check(info, tty->name, "rs_close"))
		return;

	state = info->state;
	
	local_irq_save(flags);
	
	if (tty_hung_up_p(filp)) {
		DBG_CNT("before DEC-hung");
		local_irq_restore(flags);
		return;
	}
	
#ifdef SERIAL_DEBUG_OPEN
	printk("rs_close ttys%d, count = %d\n", info->line, state->count);
#endif
	if ((tty->count == 1) && (state->count != 1)) {
		/*
		 * Uh, oh.  tty->count is 1, which means that the tty
		 * structure will be freed.  state->count should always
		 * be one in these conditions.  If it's greater than
		 * one, we've got real problems, since it means the
		 * serial port won't be shutdown.
		 */
		printk("rs_close: bad serial port count; tty->count is 1, "
		       "state->count is %d\n", state->count);
		state->count = 1;
	}
	if (--state->count < 0) {
		printk("rs_close: bad serial port count for ttys%d: %d\n",
		       info->line, state->count);
		state->count = 0;
	}
	if (state->count) {
		DBG_CNT("before DEC-2");
		local_irq_restore(flags);
		return;
	}
	info->flags |= ASYNC_CLOSING;
	/*
	 * Now we wait for the transmit buffer to clear; and we notify 
	 * the line discipline to only process XON/XOFF characters.
	 */
	tty->closing = 1;
	if (info->closing_wait != ASYNC_CLOSING_WAIT_NONE)
		tty_wait_until_sent(tty, info->closing_wait);
	/*
	 * At this point we stop accepting input.  To do this, we
	 * disable the receive line status interrupts, and tell the
	 * interrupt driver to stop checking the data ready bit in the
	 * line status register.
	 */
	info->read_status_mask &= ~BD_SC_EMPTY;
	if (info->flags & ASYNC_INITIALIZED) {

		idx = PORT_NUM(info->state->smc_scc_num);
		if (info->state->smc_scc_num & NUM_IS_SCC) {
			sccp = &pquicc->scc_regs[idx];
			sccp->scc_sccm &= ~UART_SCCM_RX;
			sccp->scc_gsmr.w.low &= ~SCC_GSMRL_ENR;
		} else {
			smcp = &pquicc->smc_regs[idx];
			smcp->smc_smcm &= ~SMCM_RX;
			smcp->smc_smcmr &= ~SMCMR_REN;
		}
		/*
		 * Before we drop DTR, make sure the UART transmitter
		 * has completely drained; this is especially
		 * important if there is a transmit FIFO!
		 */
		rs_360_wait_until_sent(tty, info->timeout);
	}
	shutdown(info);
	rs_360_flush_buffer(tty);
	tty_ldisc_flush(tty);		
	tty->closing = 0;
	info->event = 0;
	info->port.tty = NULL;
	if (info->blocked_open) {
		if (info->close_delay) {
			msleep_interruptible(jiffies_to_msecs(info->close_delay));
		}
		wake_up_interruptible(&info->open_wait);
	}
	info->flags &= ~(ASYNC_NORMAL_ACTIVE|ASYNC_CLOSING);
	wake_up_interruptible(&info->close_wait);
	local_irq_restore(flags);
}