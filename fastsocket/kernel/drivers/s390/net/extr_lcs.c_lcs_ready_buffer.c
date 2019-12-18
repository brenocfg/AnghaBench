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
struct lcs_channel {int /*<<< orphan*/  ccwdev; TYPE_1__* ccws; struct lcs_buffer* iob; } ;
struct lcs_buffer {scalar_t__ state; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ LCS_BUF_STATE_LOCKED ; 
 scalar_t__ LCS_BUF_STATE_PROCESSED ; 
 scalar_t__ LCS_BUF_STATE_READY ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  __lcs_ready_buffer_bits (struct lcs_channel*,int) ; 
 int __lcs_resume_channel (struct lcs_channel*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_ready_buffer(struct lcs_channel *channel, struct lcs_buffer *buffer)
{
	unsigned long flags;
	int index, rc;

	LCS_DBF_TEXT(5, trace, "rdybuff");
	BUG_ON(buffer->state != LCS_BUF_STATE_LOCKED &&
	       buffer->state != LCS_BUF_STATE_PROCESSED);
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	buffer->state = LCS_BUF_STATE_READY;
	index = buffer - channel->iob;
	/* Set length. */
	channel->ccws[index].count = buffer->count;
	/* Check relevant PCI/suspend bits. */
	__lcs_ready_buffer_bits(channel, index);
	rc = __lcs_resume_channel(channel);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);
	return rc;
}