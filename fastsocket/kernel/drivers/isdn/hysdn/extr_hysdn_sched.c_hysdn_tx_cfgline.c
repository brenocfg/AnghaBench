#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int debug_flags; int async_busy; unsigned short async_channel; int /*<<< orphan*/  hysdn_lock; int /*<<< orphan*/  irq_queue; scalar_t__ async_len; int /*<<< orphan*/  async_data; } ;
typedef  TYPE_1__ hysdn_card ;

/* Variables and functions */
 int ERR_ASYNC_TIME ; 
 int LOG_SCHED_ASYN ; 
 int /*<<< orphan*/  hysdn_addlog (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ strlen (unsigned char*) ; 

int
hysdn_tx_cfgline(hysdn_card *card, unsigned char *line, unsigned short chan)
{
	int cnt = 50;		/* timeout intervalls */
	unsigned long flags;

	if (card->debug_flags & LOG_SCHED_ASYN)
		hysdn_addlog(card, "async tx-cfg chan=%d len=%d", chan, strlen(line) + 1);

	while (card->async_busy) {

		if (card->debug_flags & LOG_SCHED_ASYN)
			hysdn_addlog(card, "async tx-cfg delayed");

		msleep_interruptible(20);		/* Timeout 20ms */
		if (!--cnt)
			return (-ERR_ASYNC_TIME);	/* timed out */
	}			/* wait for buffer to become free */

	spin_lock_irqsave(&card->hysdn_lock, flags);
	strcpy(card->async_data, line);
	card->async_len = strlen(line) + 1;
	card->async_channel = chan;
	card->async_busy = 1;	/* request transfer */

	/* now queue the task */
	schedule_work(&card->irq_queue);
	spin_unlock_irqrestore(&card->hysdn_lock, flags);

	if (card->debug_flags & LOG_SCHED_ASYN)
		hysdn_addlog(card, "async tx-cfg data queued");

	cnt++;			/* short delay */

	while (card->async_busy) {

		if (card->debug_flags & LOG_SCHED_ASYN)
			hysdn_addlog(card, "async tx-cfg waiting for tx-ready");

		msleep_interruptible(20);		/* Timeout 20ms */
		if (!--cnt)
			return (-ERR_ASYNC_TIME);	/* timed out */
	}			/* wait for buffer to become free again */

	if (card->debug_flags & LOG_SCHED_ASYN)
		hysdn_addlog(card, "async tx-cfg data send");

	return (0);		/* line send correctly */
}