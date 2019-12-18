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
struct tty_struct {int /*<<< orphan*/  name; struct esp_struct* driver_data; } ;
struct esp_struct {int /*<<< orphan*/  lock; scalar_t__ xmit_tail; scalar_t__ xmit_head; scalar_t__ xmit_cnt; } ;

/* Variables and functions */
 scalar_t__ serial_paranoia_check (struct esp_struct*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void rs_flush_buffer(struct tty_struct *tty)
{
	struct esp_struct *info = tty->driver_data;
	unsigned long flags;

	if (serial_paranoia_check(info, tty->name, "rs_flush_buffer"))
		return;
	spin_lock_irqsave(&info->lock, flags);
	info->xmit_cnt = info->xmit_head = info->xmit_tail = 0;
	spin_unlock_irqrestore(&info->lock, flags);
	tty_wakeup(tty);
}