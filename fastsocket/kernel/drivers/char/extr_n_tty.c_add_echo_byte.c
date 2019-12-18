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
struct tty_struct {int echo_cnt; int echo_pos; unsigned char* echo_buf; int echo_overrun; } ;

/* Variables and functions */
 unsigned char ECHO_OP_ERASE_TAB ; 
 unsigned char ECHO_OP_START ; 
 int N_TTY_BUF_SIZE ; 

__attribute__((used)) static void add_echo_byte(unsigned char c, struct tty_struct *tty)
{
	int	new_byte_pos;

	if (tty->echo_cnt == N_TTY_BUF_SIZE) {
		/* Circular buffer is already at capacity */
		new_byte_pos = tty->echo_pos;

		/*
		 * Since the buffer start position needs to be advanced,
		 * be sure to step by a whole operation byte group.
		 */
		if (tty->echo_buf[tty->echo_pos] == ECHO_OP_START) {
			if (tty->echo_buf[(tty->echo_pos + 1) &
					  (N_TTY_BUF_SIZE - 1)] ==
						ECHO_OP_ERASE_TAB) {
				tty->echo_pos += 3;
				tty->echo_cnt -= 2;
			} else {
				tty->echo_pos += 2;
				tty->echo_cnt -= 1;
			}
		} else {
			tty->echo_pos++;
		}
		tty->echo_pos &= N_TTY_BUF_SIZE - 1;

		tty->echo_overrun = 1;
	} else {
		new_byte_pos = tty->echo_pos + tty->echo_cnt;
		new_byte_pos &= N_TTY_BUF_SIZE - 1;
		tty->echo_cnt++;
	}

	tty->echo_buf[new_byte_pos] = c;
}