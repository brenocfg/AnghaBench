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
struct garmin_packet {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct garmin_data {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int FLAGS_QUEUING ; 
 int FLAGS_THROTTLED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct garmin_packet*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct garmin_packet* pkt_pop (struct garmin_data*) ; 
 int /*<<< orphan*/  send_to_tty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int garmin_flush_queue(struct garmin_data *garmin_data_p)
{
	unsigned long flags;
	struct garmin_packet *pkt;

	if ((garmin_data_p->flags & FLAGS_THROTTLED) == 0) {
		pkt = pkt_pop(garmin_data_p);
		if (pkt != NULL) {
			send_to_tty(garmin_data_p->port, pkt->data, pkt->size);
			kfree(pkt);
			mod_timer(&garmin_data_p->timer, (1)+jiffies);

		} else {
			spin_lock_irqsave(&garmin_data_p->lock, flags);
			garmin_data_p->flags &= ~FLAGS_QUEUING;
			spin_unlock_irqrestore(&garmin_data_p->lock, flags);
		}
	}
	return 0;
}