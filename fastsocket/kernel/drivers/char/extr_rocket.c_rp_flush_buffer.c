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
struct tty_struct {int /*<<< orphan*/  poll_wait; struct r_port* driver_data; } ;
struct r_port {int /*<<< orphan*/  channel; int /*<<< orphan*/  slock; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; } ;
typedef  int /*<<< orphan*/  CHANNEL_t ;

/* Variables and functions */
 scalar_t__ rocket_paranoia_check (struct r_port*,char*) ; 
 int /*<<< orphan*/  sFlushTxFIFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rp_flush_buffer(struct tty_struct *tty)
{
	struct r_port *info = tty->driver_data;
	CHANNEL_t *cp;
	unsigned long flags;

	if (rocket_paranoia_check(info, "rp_flush_buffer"))
		return;

	spin_lock_irqsave(&info->slock, flags);
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;
	spin_unlock_irqrestore(&info->slock, flags);

#ifdef ROCKETPORT_HAVE_POLL_WAIT
	wake_up_interruptible(&tty->poll_wait);
#endif
	tty_wakeup(tty);

	cp = &info->channel;
	sFlushTxFIFO(cp);
}