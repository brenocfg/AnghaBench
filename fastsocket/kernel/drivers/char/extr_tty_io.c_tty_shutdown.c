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
struct tty_struct {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty_driver_remove_tty (int /*<<< orphan*/ ,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_free_termios (struct tty_struct*) ; 

void tty_shutdown(struct tty_struct *tty)
{
	tty_driver_remove_tty(tty->driver, tty);
	tty_free_termios(tty);
}