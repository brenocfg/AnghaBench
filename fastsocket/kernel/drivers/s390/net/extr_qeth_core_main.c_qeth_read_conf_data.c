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
struct TYPE_2__ {scalar_t__ cmd_code; int count; int /*<<< orphan*/  flags; scalar_t__ cda; } ;
struct qeth_channel {scalar_t__ state; int /*<<< orphan*/  ccwdev; TYPE_1__ ccw; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; struct qeth_channel data; } ;
struct ciw {scalar_t__ cmd; int count; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 scalar_t__ CH_STATE_DOWN ; 
 scalar_t__ CH_STATE_RCD ; 
 scalar_t__ CH_STATE_RCD_DONE ; 
 int /*<<< orphan*/  CIW_TYPE_RCD ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  LPM_ANYPATH ; 
 int /*<<< orphan*/  QETH_RCD_PARM ; 
 int /*<<< orphan*/  QETH_RCD_TIMEOUT ; 
 scalar_t__ __pa (char*) ; 
 struct ciw* ccw_device_get_ciw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccw_device_start_timeout (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int qeth_read_conf_data(struct qeth_card *card, void **buffer,
			       int *length)
{
	struct ciw *ciw;
	char *rcd_buf;
	int ret;
	struct qeth_channel *channel = &card->data;
	unsigned long flags;

	/*
	 * scan for RCD command in extended SenseID data
	 */
	ciw = ccw_device_get_ciw(channel->ccwdev, CIW_TYPE_RCD);
	if (!ciw || ciw->cmd == 0)
		return -EOPNOTSUPP;
	rcd_buf = kzalloc(ciw->count, GFP_KERNEL | GFP_DMA);
	if (!rcd_buf)
		return -ENOMEM;

	channel->ccw.cmd_code = ciw->cmd;
	channel->ccw.cda = (__u32) __pa(rcd_buf);
	channel->ccw.count = ciw->count;
	channel->ccw.flags = CCW_FLAG_SLI;
	channel->state = CH_STATE_RCD;
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	ret = ccw_device_start_timeout(channel->ccwdev, &channel->ccw,
				       QETH_RCD_PARM, LPM_ANYPATH, 0,
				       QETH_RCD_TIMEOUT);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	if (!ret)
		wait_event(card->wait_q,
			   (channel->state == CH_STATE_RCD_DONE ||
			    channel->state == CH_STATE_DOWN));
	if (channel->state == CH_STATE_DOWN)
		ret = -EIO;
	else
		channel->state = CH_STATE_DOWN;
	if (ret) {
		kfree(rcd_buf);
		*buffer = NULL;
		*length = 0;
	} else {
		*length = ciw->count;
		*buffer = rcd_buf;
	}
	return ret;
}