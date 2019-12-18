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
struct tty_struct {TYPE_1__* ops; int /*<<< orphan*/  flags; int /*<<< orphan*/  atomic_write_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (struct tty_struct*,char*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_CLOSING ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_write_unlock (struct tty_struct*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

void tty_write_message(struct tty_struct *tty, char *msg)
{
	lock_kernel();
	if (tty) {
		mutex_lock(&tty->atomic_write_lock);
		if (tty->ops->write && !test_bit(TTY_CLOSING, &tty->flags))
			tty->ops->write(tty, msg, strlen(msg));
		tty_write_unlock(tty);
	}
	unlock_kernel();
	return;
}