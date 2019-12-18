#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  work; int /*<<< orphan*/  lock; TYPE_1__* tail; } ;
struct tty_struct {TYPE_2__ buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  used; int /*<<< orphan*/  commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void tty_schedule_flip(struct tty_struct *tty)
{
	unsigned long flags;
	spin_lock_irqsave(&tty->buf.lock, flags);
	if (tty->buf.tail != NULL)
		tty->buf.tail->commit = tty->buf.tail->used;
	spin_unlock_irqrestore(&tty->buf.lock, flags);
	schedule_delayed_work(&tty->buf.work, 1);
}