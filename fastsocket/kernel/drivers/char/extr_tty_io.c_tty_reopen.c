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
struct tty_struct {int /*<<< orphan*/  ldisc_mutex; int /*<<< orphan*/  flags; struct tty_driver* driver; scalar_t__ count; TYPE_1__* link; } ;
struct tty_driver {scalar_t__ type; scalar_t__ subtype; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ PTY_TYPE_MASTER ; 
 int /*<<< orphan*/  TTY_CLOSING ; 
 scalar_t__ TTY_DRIVER_TYPE_PTY ; 
 int /*<<< orphan*/  TTY_LDISC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_reopen(struct tty_struct *tty)
{
	struct tty_driver *driver = tty->driver;

	if (test_bit(TTY_CLOSING, &tty->flags))
		return -EIO;

	if (driver->type == TTY_DRIVER_TYPE_PTY &&
	    driver->subtype == PTY_TYPE_MASTER) {
		/*
		 * special case for PTY masters: only one open permitted,
		 * and the slave side open count is incremented as well.
		 */
		if (tty->count)
			return -EIO;

		tty->link->count++;
	}
	tty->count++;
	tty->driver = driver; /* N.B. why do this every time?? */

	mutex_lock(&tty->ldisc_mutex);
	WARN_ON(!test_bit(TTY_LDISC, &tty->flags));
	mutex_unlock(&tty->ldisc_mutex);

	return 0;
}