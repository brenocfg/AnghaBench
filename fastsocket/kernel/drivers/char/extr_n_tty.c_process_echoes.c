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
struct tty_struct {int echo_cnt; unsigned char* echo_buf; int echo_pos; unsigned int canon_column; unsigned int column; TYPE_1__* ops; int /*<<< orphan*/  output_lock; int /*<<< orphan*/  echo_lock; scalar_t__ echo_overrun; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_chars ) (struct tty_struct*) ;} ;

/* Variables and functions */
#define  ECHO_OP_ERASE_TAB 131 
#define  ECHO_OP_MOVE_BACK_COL 130 
#define  ECHO_OP_SET_CANON_COL 129 
#define  ECHO_OP_START 128 
 int N_TTY_BUF_SIZE ; 
 scalar_t__ O_OPOST (struct tty_struct*) ; 
 int /*<<< orphan*/  TTY_HW_COOK_OUT ; 
 int do_output_char (unsigned char,struct tty_struct*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_put_char (struct tty_struct*,unsigned char const) ; 
 int tty_write_room (struct tty_struct*) ; 

__attribute__((used)) static void process_echoes(struct tty_struct *tty)
{
	int	space, nr;
	unsigned char c;
	unsigned char *cp, *buf_end;

	if (!tty->echo_cnt)
		return;

	mutex_lock(&tty->output_lock);
	mutex_lock(&tty->echo_lock);

	space = tty_write_room(tty);

	buf_end = tty->echo_buf + N_TTY_BUF_SIZE;
	cp = tty->echo_buf + tty->echo_pos;
	nr = tty->echo_cnt;
	while (nr > 0) {
		c = *cp;
		if (c == ECHO_OP_START) {
			unsigned char op;
			unsigned char *opp;
			int no_space_left = 0;

			/*
			 * If the buffer byte is the start of a multi-byte
			 * operation, get the next byte, which is either the
			 * op code or a control character value.
			 */
			opp = cp + 1;
			if (opp == buf_end)
				opp -= N_TTY_BUF_SIZE;
			op = *opp;

			switch (op) {
				unsigned int num_chars, num_bs;

			case ECHO_OP_ERASE_TAB:
				if (++opp == buf_end)
					opp -= N_TTY_BUF_SIZE;
				num_chars = *opp;

				/*
				 * Determine how many columns to go back
				 * in order to erase the tab.
				 * This depends on the number of columns
				 * used by other characters within the tab
				 * area.  If this (modulo 8) count is from
				 * the start of input rather than from a
				 * previous tab, we offset by canon column.
				 * Otherwise, tab spacing is normal.
				 */
				if (!(num_chars & 0x80))
					num_chars += tty->canon_column;
				num_bs = 8 - (num_chars & 7);

				if (num_bs > space) {
					no_space_left = 1;
					break;
				}
				space -= num_bs;
				while (num_bs--) {
					tty_put_char(tty, '\b');
					if (tty->column > 0)
						tty->column--;
				}
				cp += 3;
				nr -= 3;
				break;

			case ECHO_OP_SET_CANON_COL:
				tty->canon_column = tty->column;
				cp += 2;
				nr -= 2;
				break;

			case ECHO_OP_MOVE_BACK_COL:
				if (tty->column > 0)
					tty->column--;
				cp += 2;
				nr -= 2;
				break;

			case ECHO_OP_START:
				/* This is an escaped echo op start code */
				if (!space) {
					no_space_left = 1;
					break;
				}
				tty_put_char(tty, ECHO_OP_START);
				tty->column++;
				space--;
				cp += 2;
				nr -= 2;
				break;

			default:
				/*
				 * If the op is not a special byte code,
				 * it is a ctrl char tagged to be echoed
				 * as "^X" (where X is the letter
				 * representing the control char).
				 * Note that we must ensure there is
				 * enough space for the whole ctrl pair.
				 *
				 */
				if (space < 2) {
					no_space_left = 1;
					break;
				}
				tty_put_char(tty, '^');
				tty_put_char(tty, op ^ 0100);
				tty->column += 2;
				space -= 2;
				cp += 2;
				nr -= 2;
			}

			if (no_space_left)
				break;
		} else {
			if (O_OPOST(tty) &&
			    !(test_bit(TTY_HW_COOK_OUT, &tty->flags))) {
				int retval = do_output_char(c, tty, space);
				if (retval < 0)
					break;
				space -= retval;
			} else {
				if (!space)
					break;
				tty_put_char(tty, c);
				space -= 1;
			}
			cp += 1;
			nr -= 1;
		}

		/* When end of circular buffer reached, wrap around */
		if (cp >= buf_end)
			cp -= N_TTY_BUF_SIZE;
	}

	if (nr == 0) {
		tty->echo_pos = 0;
		tty->echo_cnt = 0;
		tty->echo_overrun = 0;
	} else {
		int num_processed = tty->echo_cnt - nr;
		tty->echo_pos += num_processed;
		tty->echo_pos &= N_TTY_BUF_SIZE - 1;
		tty->echo_cnt = nr;
		if (num_processed > 0)
			tty->echo_overrun = 0;
	}

	mutex_unlock(&tty->echo_lock);
	mutex_unlock(&tty->output_lock);

	if (tty->ops->flush_chars)
		tty->ops->flush_chars(tty);
}