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
struct tty_struct {scalar_t__ flow_change; int /*<<< orphan*/  termios_mutex; TYPE_1__* ops; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* throttle ) (struct tty_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_THROTTLED ; 
 scalar_t__ TTY_THROTTLE_SAFE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int tty_throttle_safe(struct tty_struct *tty)
{
	int ret = 0;

	mutex_lock(&tty->termios_mutex);
	if (!test_bit(TTY_THROTTLED, &tty->flags)) {
		if (tty->flow_change != TTY_THROTTLE_SAFE)
			ret = 1;
		else {
			__set_bit(TTY_THROTTLED, &tty->flags);
			if (tty->ops->throttle)
				tty->ops->throttle(tty);
		}
	}
	mutex_unlock(&tty->termios_mutex);

	return ret;
}