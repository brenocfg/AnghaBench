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
struct tty_struct {int minimum_to_wake; scalar_t__ closing; scalar_t__ column; void* echo_buf; void* read_buf; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  N_TTY_BUF_SIZE ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_tty_set_termios (struct tty_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_buffer_flags (struct tty_struct*) ; 

__attribute__((used)) static int n_tty_open(struct tty_struct *tty)
{
	if (!tty)
		return -EINVAL;

	/* These are ugly. Currently a malloc failure here can panic */
	if (!tty->read_buf) {
		tty->read_buf = kzalloc(N_TTY_BUF_SIZE, GFP_KERNEL);
		if (!tty->read_buf)
			return -ENOMEM;
	}
	if (!tty->echo_buf) {
		tty->echo_buf = kzalloc(N_TTY_BUF_SIZE, GFP_KERNEL);

		if (!tty->echo_buf)
			return -ENOMEM;
	}
	reset_buffer_flags(tty);
	tty->column = 0;
	n_tty_set_termios(tty, NULL);
	tty->minimum_to_wake = 1;
	tty->closing = 0;
	return 0;
}