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
struct tty_struct {int icanon; int raw; int real_raw; int /*<<< orphan*/  read_wait; int /*<<< orphan*/  write_wait; TYPE_2__* driver; int /*<<< orphan*/ * process_char_map; int /*<<< orphan*/  flags; scalar_t__ read_cnt; scalar_t__ erasing; scalar_t__ canon_data; int /*<<< orphan*/  read_tail; int /*<<< orphan*/  canon_head; int /*<<< orphan*/  read_flags; TYPE_1__* termios; } ;
struct ktermios {int c_lflag; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_3__ {int c_lflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 char EOF_CHAR (struct tty_struct*) ; 
 char EOL2_CHAR (struct tty_struct*) ; 
 char EOL_CHAR (struct tty_struct*) ; 
 char ERASE_CHAR (struct tty_struct*) ; 
 int ICANON ; 
 char INTR_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  I_BRKINT (struct tty_struct*) ; 
 scalar_t__ I_ICRNL (struct tty_struct*) ; 
 scalar_t__ I_IGNBRK (struct tty_struct*) ; 
 scalar_t__ I_IGNCR (struct tty_struct*) ; 
 scalar_t__ I_IGNPAR (struct tty_struct*) ; 
 scalar_t__ I_INLCR (struct tty_struct*) ; 
 int /*<<< orphan*/  I_INPCK (struct tty_struct*) ; 
 scalar_t__ I_ISTRIP (struct tty_struct*) ; 
 scalar_t__ I_IUCLC (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 char KILL_CHAR (struct tty_struct*) ; 
 char LNEXT_CHAR (struct tty_struct*) ; 
 scalar_t__ L_ECHO (struct tty_struct*) ; 
 scalar_t__ L_ICANON (struct tty_struct*) ; 
 scalar_t__ L_IEXTEN (struct tty_struct*) ; 
 scalar_t__ L_ISIG (struct tty_struct*) ; 
 char QUIT_CHAR (struct tty_struct*) ; 
 char REPRINT_CHAR (struct tty_struct*) ; 
 char START_CHAR (struct tty_struct*) ; 
 char STOP_CHAR (struct tty_struct*) ; 
 char SUSP_CHAR (struct tty_struct*) ; 
 int TTY_DRIVER_REAL_RAW ; 
 int /*<<< orphan*/  TTY_HW_COOK_IN ; 
 char WERASE_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  __DISABLED_CHAR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  n_tty_set_room (struct tty_struct*) ; 
 int /*<<< orphan*/  set_bit (char,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void n_tty_set_termios(struct tty_struct *tty, struct ktermios *old)
{
	int canon_change = 1;
	BUG_ON(!tty);

	if (old)
		canon_change = (old->c_lflag ^ tty->termios->c_lflag) & ICANON;
	if (canon_change) {
		memset(&tty->read_flags, 0, sizeof tty->read_flags);
		tty->canon_head = tty->read_tail;
		tty->canon_data = 0;
		tty->erasing = 0;
	}

	if (canon_change && !L_ICANON(tty) && tty->read_cnt)
		wake_up_interruptible(&tty->read_wait);

	tty->icanon = (L_ICANON(tty) != 0);
	if (test_bit(TTY_HW_COOK_IN, &tty->flags)) {
		tty->raw = 1;
		tty->real_raw = 1;
		n_tty_set_room(tty);
		return;
	}
	if (I_ISTRIP(tty) || I_IUCLC(tty) || I_IGNCR(tty) ||
	    I_ICRNL(tty) || I_INLCR(tty) || L_ICANON(tty) ||
	    I_IXON(tty) || L_ISIG(tty) || L_ECHO(tty) ||
	    I_PARMRK(tty)) {
		memset(tty->process_char_map, 0, 256/8);

		if (I_IGNCR(tty) || I_ICRNL(tty))
			set_bit('\r', tty->process_char_map);
		if (I_INLCR(tty))
			set_bit('\n', tty->process_char_map);

		if (L_ICANON(tty)) {
			set_bit(ERASE_CHAR(tty), tty->process_char_map);
			set_bit(KILL_CHAR(tty), tty->process_char_map);
			set_bit(EOF_CHAR(tty), tty->process_char_map);
			set_bit('\n', tty->process_char_map);
			set_bit(EOL_CHAR(tty), tty->process_char_map);
			if (L_IEXTEN(tty)) {
				set_bit(WERASE_CHAR(tty),
					tty->process_char_map);
				set_bit(LNEXT_CHAR(tty),
					tty->process_char_map);
				set_bit(EOL2_CHAR(tty),
					tty->process_char_map);
				if (L_ECHO(tty))
					set_bit(REPRINT_CHAR(tty),
						tty->process_char_map);
			}
		}
		if (I_IXON(tty)) {
			set_bit(START_CHAR(tty), tty->process_char_map);
			set_bit(STOP_CHAR(tty), tty->process_char_map);
		}
		if (L_ISIG(tty)) {
			set_bit(INTR_CHAR(tty), tty->process_char_map);
			set_bit(QUIT_CHAR(tty), tty->process_char_map);
			set_bit(SUSP_CHAR(tty), tty->process_char_map);
		}
		clear_bit(__DISABLED_CHAR, tty->process_char_map);
		tty->raw = 0;
		tty->real_raw = 0;
	} else {
		tty->raw = 1;
		if ((I_IGNBRK(tty) || (!I_BRKINT(tty) && !I_PARMRK(tty))) &&
		    (I_IGNPAR(tty) || !I_INPCK(tty)) &&
		    (tty->driver->flags & TTY_DRIVER_REAL_RAW))
			tty->real_raw = 1;
		else
			tty->real_raw = 0;
	}
	n_tty_set_room(tty);
	/* The termios change make the tty ready for I/O */
	wake_up_interruptible(&tty->write_wait);
	wake_up_interruptible(&tty->read_wait);
}