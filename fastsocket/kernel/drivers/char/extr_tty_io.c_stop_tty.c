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
struct tty_struct {int stopped; TYPE_2__* ops; int /*<<< orphan*/  ctrl_lock; TYPE_1__* link; int /*<<< orphan*/  ctrl_status; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (struct tty_struct*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  read_wait; scalar_t__ packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  TIOCPKT_START ; 
 int /*<<< orphan*/  TIOCPKT_STOP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void stop_tty(struct tty_struct *tty)
{
	unsigned long flags;
	spin_lock_irqsave(&tty->ctrl_lock, flags);
	if (tty->stopped) {
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		return;
	}
	tty->stopped = 1;
	if (tty->link && tty->link->packet) {
		tty->ctrl_status &= ~TIOCPKT_START;
		tty->ctrl_status |= TIOCPKT_STOP;
		wake_up_interruptible_poll(&tty->link->read_wait, POLLIN);
	}
	spin_unlock_irqrestore(&tty->ctrl_lock, flags);
	if (tty->ops->stop)
		(tty->ops->stop)(tty);
}