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
struct tty_struct {int lnext; int read_cnt; scalar_t__ canon_head; scalar_t__ read_head; unsigned char* read_buf; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  fasync; int /*<<< orphan*/  read_lock; int /*<<< orphan*/  canon_data; int /*<<< orphan*/ * read_flags; int /*<<< orphan*/  flags; scalar_t__ icanon; scalar_t__ pgrp; int /*<<< orphan*/  process_char_map; scalar_t__ closing; int /*<<< orphan*/  flow_stopped; scalar_t__ stopped; scalar_t__ raw; } ;

/* Variables and functions */
 unsigned char EOF_CHAR (struct tty_struct*) ; 
 unsigned char EOL2_CHAR (struct tty_struct*) ; 
 unsigned char EOL_CHAR (struct tty_struct*) ; 
 unsigned char ERASE_CHAR (struct tty_struct*) ; 
 unsigned char INTR_CHAR (struct tty_struct*) ; 
 scalar_t__ I_ICRNL (struct tty_struct*) ; 
 scalar_t__ I_IGNCR (struct tty_struct*) ; 
 scalar_t__ I_INLCR (struct tty_struct*) ; 
 scalar_t__ I_ISTRIP (struct tty_struct*) ; 
 scalar_t__ I_IUCLC (struct tty_struct*) ; 
 scalar_t__ I_IXANY (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 unsigned char KILL_CHAR (struct tty_struct*) ; 
 unsigned char LNEXT_CHAR (struct tty_struct*) ; 
 scalar_t__ L_ECHO (struct tty_struct*) ; 
 scalar_t__ L_ECHOCTL (struct tty_struct*) ; 
 scalar_t__ L_ECHONL (struct tty_struct*) ; 
 scalar_t__ L_IEXTEN (struct tty_struct*) ; 
 scalar_t__ L_ISIG (struct tty_struct*) ; 
 int /*<<< orphan*/  L_NOFLSH (struct tty_struct*) ; 
 int N_TTY_BUF_SIZE ; 
 int /*<<< orphan*/  POLL_IN ; 
 unsigned char QUIT_CHAR (struct tty_struct*) ; 
 unsigned char REPRINT_CHAR (struct tty_struct*) ; 
 int SIGINT ; 
 int /*<<< orphan*/  SIGIO ; 
 int SIGQUIT ; 
 int SIGTSTP ; 
 unsigned char START_CHAR (struct tty_struct*) ; 
 unsigned char STOP_CHAR (struct tty_struct*) ; 
 unsigned char SUSP_CHAR (struct tty_struct*) ; 
 scalar_t__ TTY_PUSH ; 
 unsigned char WERASE_CHAR (struct tty_struct*) ; 
 unsigned char __DISABLED_CHAR ; 
 int /*<<< orphan*/  echo_char (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  echo_char_raw (char,struct tty_struct*) ; 
 int /*<<< orphan*/  echo_set_canon_col (struct tty_struct*) ; 
 int /*<<< orphan*/  eraser (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  finish_erasing (struct tty_struct*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_pgrp (scalar_t__,int,int) ; 
 int /*<<< orphan*/  n_tty_flush_buffer (struct tty_struct*) ; 
 int /*<<< orphan*/  process_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  process_output (char,struct tty_struct*) ; 
 int /*<<< orphan*/  put_tty_queue (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  put_tty_queue_nolock (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  start_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  stop_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  test_bit (unsigned char,int /*<<< orphan*/ ) ; 
 unsigned char tolower (unsigned char) ; 
 int /*<<< orphan*/  tty_driver_flush_buffer (struct tty_struct*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void n_tty_receive_char(struct tty_struct *tty, unsigned char c)
{
	unsigned long flags;
	int parmrk;

	if (tty->raw) {
		put_tty_queue(c, tty);
		return;
	}

	if (I_ISTRIP(tty))
		c &= 0x7f;
	if (I_IUCLC(tty) && L_IEXTEN(tty))
		c = tolower(c);

	if (tty->stopped && !tty->flow_stopped && I_IXON(tty) &&
	    I_IXANY(tty) && c != START_CHAR(tty) && c != STOP_CHAR(tty) &&
	    c != INTR_CHAR(tty) && c != QUIT_CHAR(tty) && c != SUSP_CHAR(tty)) {
		start_tty(tty);
		process_echoes(tty);
	}

	if (tty->closing) {
		if (I_IXON(tty)) {
			if (c == START_CHAR(tty)) {
				start_tty(tty);
				process_echoes(tty);
			} else if (c == STOP_CHAR(tty))
				stop_tty(tty);
		}
		return;
	}

	/*
	 * If the previous character was LNEXT, or we know that this
	 * character is not one of the characters that we'll have to
	 * handle specially, do shortcut processing to speed things
	 * up.
	 */
	if (!test_bit(c, tty->process_char_map) || tty->lnext) {
		tty->lnext = 0;
		parmrk = (c == (unsigned char) '\377' && I_PARMRK(tty)) ? 1 : 0;
		if (tty->read_cnt >= (N_TTY_BUF_SIZE - parmrk - 1)) {
			/* beep if no space */
			if (L_ECHO(tty))
				process_output('\a', tty);
			return;
		}
		if (L_ECHO(tty)) {
			finish_erasing(tty);
			/* Record the column of first canon char. */
			if (tty->canon_head == tty->read_head)
				echo_set_canon_col(tty);
			echo_char(c, tty);
			process_echoes(tty);
		}
		if (parmrk)
			put_tty_queue(c, tty);
		put_tty_queue(c, tty);
		return;
	}

	if (I_IXON(tty)) {
		if (c == START_CHAR(tty)) {
			start_tty(tty);
			process_echoes(tty);
			return;
		}
		if (c == STOP_CHAR(tty)) {
			stop_tty(tty);
			return;
		}
	}

	if (L_ISIG(tty)) {
		int signal;
		signal = SIGINT;
		if (c == INTR_CHAR(tty))
			goto send_signal;
		signal = SIGQUIT;
		if (c == QUIT_CHAR(tty))
			goto send_signal;
		signal = SIGTSTP;
		if (c == SUSP_CHAR(tty)) {
send_signal:
			/*
			 * Note that we do not use isig() here because we want
			 * the order to be:
			 * 1) flush, 2) echo, 3) signal
			 */
			if (!L_NOFLSH(tty)) {
				n_tty_flush_buffer(tty);
				tty_driver_flush_buffer(tty);
			}
			if (I_IXON(tty))
				start_tty(tty);
			if (L_ECHO(tty)) {
				echo_char(c, tty);
				process_echoes(tty);
			}
			if (tty->pgrp)
				kill_pgrp(tty->pgrp, signal, 1);
			return;
		}
	}

	if (c == '\r') {
		if (I_IGNCR(tty))
			return;
		if (I_ICRNL(tty))
			c = '\n';
	} else if (c == '\n' && I_INLCR(tty))
		c = '\r';

	if (tty->icanon) {
		if (c == ERASE_CHAR(tty) || c == KILL_CHAR(tty) ||
		    (c == WERASE_CHAR(tty) && L_IEXTEN(tty))) {
			eraser(c, tty);
			process_echoes(tty);
			return;
		}
		if (c == LNEXT_CHAR(tty) && L_IEXTEN(tty)) {
			tty->lnext = 1;
			if (L_ECHO(tty)) {
				finish_erasing(tty);
				if (L_ECHOCTL(tty)) {
					echo_char_raw('^', tty);
					echo_char_raw('\b', tty);
					process_echoes(tty);
				}
			}
			return;
		}
		if (c == REPRINT_CHAR(tty) && L_ECHO(tty) &&
		    L_IEXTEN(tty)) {
			unsigned long tail = tty->canon_head;

			finish_erasing(tty);
			echo_char(c, tty);
			echo_char_raw('\n', tty);
			while (tail != tty->read_head) {
				echo_char(tty->read_buf[tail], tty);
				tail = (tail+1) & (N_TTY_BUF_SIZE-1);
			}
			process_echoes(tty);
			return;
		}
		if (c == '\n') {
			if (tty->read_cnt >= N_TTY_BUF_SIZE) {
				if (L_ECHO(tty))
					process_output('\a', tty);
				return;
			}
			if (L_ECHO(tty) || L_ECHONL(tty)) {
				echo_char_raw('\n', tty);
				process_echoes(tty);
			}
			goto handle_newline;
		}
		if (c == EOF_CHAR(tty)) {
			if (tty->read_cnt >= N_TTY_BUF_SIZE)
				return;
			if (tty->canon_head != tty->read_head)
				set_bit(TTY_PUSH, &tty->flags);
			c = __DISABLED_CHAR;
			goto handle_newline;
		}
		if ((c == EOL_CHAR(tty)) ||
		    (c == EOL2_CHAR(tty) && L_IEXTEN(tty))) {
			parmrk = (c == (unsigned char) '\377' && I_PARMRK(tty))
				 ? 1 : 0;
			if (tty->read_cnt >= (N_TTY_BUF_SIZE - parmrk)) {
				if (L_ECHO(tty))
					process_output('\a', tty);
				return;
			}
			/*
			 * XXX are EOL_CHAR and EOL2_CHAR echoed?!?
			 */
			if (L_ECHO(tty)) {
				/* Record the column of first canon char. */
				if (tty->canon_head == tty->read_head)
					echo_set_canon_col(tty);
				echo_char(c, tty);
				process_echoes(tty);
			}
			/*
			 * XXX does PARMRK doubling happen for
			 * EOL_CHAR and EOL2_CHAR?
			 */
			if (parmrk)
				put_tty_queue(c, tty);

handle_newline:
			spin_lock_irqsave(&tty->read_lock, flags);
			set_bit(tty->read_head, tty->read_flags);
			put_tty_queue_nolock(c, tty);
			tty->canon_head = tty->read_head;
			tty->canon_data++;
			spin_unlock_irqrestore(&tty->read_lock, flags);
			kill_fasync(&tty->fasync, SIGIO, POLL_IN);
			if (waitqueue_active(&tty->read_wait))
				wake_up_interruptible(&tty->read_wait);
			return;
		}
	}

	parmrk = (c == (unsigned char) '\377' && I_PARMRK(tty)) ? 1 : 0;
	if (tty->read_cnt >= (N_TTY_BUF_SIZE - parmrk - 1)) {
		/* beep if no space */
		if (L_ECHO(tty))
			process_output('\a', tty);
		return;
	}
	if (L_ECHO(tty)) {
		finish_erasing(tty);
		if (c == '\n')
			echo_char_raw('\n', tty);
		else {
			/* Record the column of first canon char. */
			if (tty->canon_head == tty->read_head)
				echo_set_canon_col(tty);
			echo_char(c, tty);
		}
		process_echoes(tty);
	}

	if (parmrk)
		put_tty_queue(c, tty);

	put_tty_queue(c, tty);
}