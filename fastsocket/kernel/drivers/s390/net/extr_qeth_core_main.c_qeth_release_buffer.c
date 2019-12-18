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
struct qeth_cmd_buffer {scalar_t__ rc; int /*<<< orphan*/  callback; int /*<<< orphan*/  state; int /*<<< orphan*/  data; } ;
struct qeth_channel {int /*<<< orphan*/  wait_q; int /*<<< orphan*/  iob_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_STATE_FREE ; 
 int /*<<< orphan*/  QETH_BUFSIZE ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_send_control_data_cb ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void qeth_release_buffer(struct qeth_channel *channel,
		struct qeth_cmd_buffer *iob)
{
	unsigned long flags;

	QETH_DBF_TEXT(TRACE, 6, "relbuff");
	spin_lock_irqsave(&channel->iob_lock, flags);
	memset(iob->data, 0, QETH_BUFSIZE);
	iob->state = BUF_STATE_FREE;
	iob->callback = qeth_send_control_data_cb;
	iob->rc = 0;
	spin_unlock_irqrestore(&channel->iob_lock, flags);
	wake_up(&channel->wait_q);
}