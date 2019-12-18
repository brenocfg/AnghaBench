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
struct qeth_channel {scalar_t__ state; int /*<<< orphan*/  ccwdev; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; } ;

/* Variables and functions */
 struct qeth_card* CARD_FROM_CDEV (int /*<<< orphan*/ ) ; 
 scalar_t__ CH_STATE_HALTED ; 
 int ERESTARTSYS ; 
 int ETIME ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_HALT_CHANNEL_PARM ; 
 int /*<<< orphan*/  QETH_TIMEOUT ; 
 int /*<<< orphan*/  TRACE ; 
 int ccw_device_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_halt_channel(struct qeth_channel *channel)
{
	unsigned long flags;
	struct qeth_card *card;
	int rc;

	QETH_DBF_TEXT(TRACE, 3, "haltch");
	card = CARD_FROM_CDEV(channel->ccwdev);
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_halt(channel->ccwdev, QETH_HALT_CHANNEL_PARM);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);

	if (rc)
		return rc;
	rc = wait_event_interruptible_timeout(card->wait_q,
			channel->state == CH_STATE_HALTED, QETH_TIMEOUT);
	if (rc == -ERESTARTSYS)
		return rc;
	if (channel->state != CH_STATE_HALTED)
		return -ETIME;
	return 0;
}