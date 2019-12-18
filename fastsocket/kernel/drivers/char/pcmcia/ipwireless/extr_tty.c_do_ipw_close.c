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
struct tty_struct {int /*<<< orphan*/ * driver_data; } ;
struct ipw_tty {scalar_t__ open_count; scalar_t__ tty_type; int /*<<< orphan*/  network; struct tty_struct* linux_tty; } ;

/* Variables and functions */
 scalar_t__ TTYTYPE_MODEM ; 
 int /*<<< orphan*/  ipwireless_ppp_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_ipw_close(struct ipw_tty *tty)
{
	tty->open_count--;

	if (tty->open_count == 0) {
		struct tty_struct *linux_tty = tty->linux_tty;

		if (linux_tty != NULL) {
			tty->linux_tty = NULL;
			linux_tty->driver_data = NULL;

			if (tty->tty_type == TTYTYPE_MODEM)
				ipwireless_ppp_close(tty->network);
		}
	}
}