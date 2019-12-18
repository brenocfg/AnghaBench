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
struct tty_struct {int /*<<< orphan*/ * echo_buf; int /*<<< orphan*/ * read_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_tty_flush_buffer (struct tty_struct*) ; 

__attribute__((used)) static void n_tty_close(struct tty_struct *tty)
{
	n_tty_flush_buffer(tty);
	if (tty->read_buf) {
		kfree(tty->read_buf);
		tty->read_buf = NULL;
	}
	if (tty->echo_buf) {
		kfree(tty->echo_buf);
		tty->echo_buf = NULL;
	}
}