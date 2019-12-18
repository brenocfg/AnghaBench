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
struct lcs_channel {int buf_idx; scalar_t__ state; size_t io_idx; int /*<<< orphan*/  wait_q; TYPE_1__* ccwdev; struct lcs_buffer* iob; } ;
struct lcs_buffer {scalar_t__ state; int /*<<< orphan*/  (* callback ) (struct lcs_channel*,struct lcs_buffer*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ LCS_BUF_STATE_PROCESSED ; 
 scalar_t__ LCS_BUF_STATE_READY ; 
 scalar_t__ LCS_CH_STATE_STOPPED ; 
 scalar_t__ LCS_CH_STATE_SUSPENDED ; 
 int /*<<< orphan*/  LCS_DBF_TEXT_ (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int LCS_NUM_BUFFS ; 
 int __lcs_resume_channel (struct lcs_channel*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_1__*) ; 
 int lcs_start_channel (struct lcs_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct lcs_channel*,struct lcs_buffer*) ; 
 int /*<<< orphan*/  trace ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lcs_tasklet(unsigned long data)
{
	unsigned long flags;
	struct lcs_channel *channel;
	struct lcs_buffer *iob;
	int buf_idx;
	int rc;

	channel = (struct lcs_channel *) data;
	LCS_DBF_TEXT_(5, trace, "tlet%s", dev_name(&channel->ccwdev->dev));

	/* Check for processed buffers. */
	iob = channel->iob;
	buf_idx = channel->buf_idx;
	while (iob[buf_idx].state == LCS_BUF_STATE_PROCESSED) {
		/* Do the callback thing. */
		if (iob[buf_idx].callback != NULL)
			iob[buf_idx].callback(channel, iob + buf_idx);
		buf_idx = (buf_idx + 1) & (LCS_NUM_BUFFS - 1);
	}
	channel->buf_idx = buf_idx;

	if (channel->state == LCS_CH_STATE_STOPPED)
		// FIXME: what if rc != 0 ??
		rc = lcs_start_channel(channel);
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	if (channel->state == LCS_CH_STATE_SUSPENDED &&
	    channel->iob[channel->io_idx].state == LCS_BUF_STATE_READY) {
		// FIXME: what if rc != 0 ??
		rc = __lcs_resume_channel(channel);
	}
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);

	/* Something happened on the channel. Wake up waiters. */
	wake_up(&channel->wait_q);
}