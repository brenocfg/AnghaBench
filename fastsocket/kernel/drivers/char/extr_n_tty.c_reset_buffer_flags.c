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
struct tty_struct {int /*<<< orphan*/  read_flags; scalar_t__ erasing; scalar_t__ canon_data; scalar_t__ canon_head; int /*<<< orphan*/  echo_lock; scalar_t__ echo_overrun; scalar_t__ echo_cnt; scalar_t__ echo_pos; int /*<<< orphan*/  read_lock; scalar_t__ read_cnt; scalar_t__ read_tail; scalar_t__ read_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_unthrottle (struct tty_struct*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_tty_set_room (struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void reset_buffer_flags(struct tty_struct *tty)
{
	unsigned long flags;

	spin_lock_irqsave(&tty->read_lock, flags);
	tty->read_head = tty->read_tail = tty->read_cnt = 0;
	spin_unlock_irqrestore(&tty->read_lock, flags);

	mutex_lock(&tty->echo_lock);
	tty->echo_pos = tty->echo_cnt = tty->echo_overrun = 0;
	mutex_unlock(&tty->echo_lock);

	tty->canon_head = tty->canon_data = tty->erasing = 0;
	memset(&tty->read_flags, 0, sizeof tty->read_flags);
	n_tty_set_room(tty);
	check_unthrottle(tty);
}