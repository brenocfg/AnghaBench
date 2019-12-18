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
struct tty_struct {int /*<<< orphan*/  read_wait; } ;

/* Variables and functions */
 scalar_t__ I_BRKINT (struct tty_struct*) ; 
 scalar_t__ I_IGNBRK (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  isig (int /*<<< orphan*/ ,struct tty_struct*,int) ; 
 int /*<<< orphan*/  put_tty_queue (char,struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void n_tty_receive_break(struct tty_struct *tty)
{
	if (I_IGNBRK(tty))
		return;
	if (I_BRKINT(tty)) {
		isig(SIGINT, tty, 1);
		return;
	}
	if (I_PARMRK(tty)) {
		put_tty_queue('\377', tty);
		put_tty_queue('\0', tty);
	}
	put_tty_queue('\0', tty);
	wake_up_interruptible(&tty->read_wait);
}