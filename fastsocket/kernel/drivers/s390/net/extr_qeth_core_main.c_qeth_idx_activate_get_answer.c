#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qeth_cmd_buffer {void (* callback ) (struct qeth_channel*,struct qeth_cmd_buffer*) ;int /*<<< orphan*/  data; } ;
struct TYPE_3__ {scalar_t__ cda; int /*<<< orphan*/  count; } ;
struct qeth_channel {scalar_t__ state; int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  ccwdev; TYPE_1__ ccw; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; } ;
struct ccw1 {int dummy; } ;
typedef  int /*<<< orphan*/  addr_t ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 struct qeth_card* CARD_FROM_CDEV (int /*<<< orphan*/ ) ; 
 scalar_t__ CH_STATE_UP ; 
 int ERESTARTSYS ; 
 int ETIME ; 
 int /*<<< orphan*/  QETH_BUFSIZE ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  QETH_TIMEOUT ; 
 int /*<<< orphan*/  READ_CCW ; 
 int /*<<< orphan*/  SETUP ; 
 scalar_t__ __pa (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ccw_device_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qeth_clear_cmd_buffers (struct qeth_channel*) ; 
 struct qeth_cmd_buffer* qeth_get_buffer (struct qeth_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_idx_activate_get_answer(struct qeth_channel *channel,
		void (*idx_reply_cb)(struct qeth_channel *,
			struct qeth_cmd_buffer *))
{
	struct qeth_cmd_buffer *iob;
	unsigned long flags;
	int rc;
	struct qeth_card *card;

	QETH_DBF_TEXT(SETUP, 2, "idxanswr");
	card = CARD_FROM_CDEV(channel->ccwdev);
	iob = qeth_get_buffer(channel);
	iob->callback = idx_reply_cb;
	memcpy(&channel->ccw, READ_CCW, sizeof(struct ccw1));
	channel->ccw.count = QETH_BUFSIZE;
	channel->ccw.cda = (__u32) __pa(iob->data);

	wait_event(card->wait_q,
		   atomic_cmpxchg(&channel->irq_pending, 0, 1) == 0);
	QETH_DBF_TEXT(SETUP, 6, "noirqpnd");
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_start(channel->ccwdev,
			      &channel->ccw, (addr_t) iob, 0, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);

	if (rc) {
		QETH_DBF_MESSAGE(2, "Error2 in activating channel rc=%d\n", rc);
		QETH_DBF_TEXT_(SETUP, 2, "2err%d", rc);
		atomic_set(&channel->irq_pending, 0);
		wake_up(&card->wait_q);
		return rc;
	}
	rc = wait_event_interruptible_timeout(card->wait_q,
			 channel->state == CH_STATE_UP, QETH_TIMEOUT);
	if (rc == -ERESTARTSYS)
		return rc;
	if (channel->state != CH_STATE_UP) {
		rc = -ETIME;
		QETH_DBF_TEXT_(SETUP, 2, "3err%d", rc);
		qeth_clear_cmd_buffers(channel);
	} else
		rc = 0;
	return rc;
}