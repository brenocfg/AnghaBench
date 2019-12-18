#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int (* callback ) (struct qeth_card*,struct qeth_reply*,unsigned long) ;int rc; int /*<<< orphan*/  received; TYPE_3__* card; int /*<<< orphan*/  list; int /*<<< orphan*/  wait_q; scalar_t__ seqno; void* param; } ;
struct TYPE_8__ {scalar_t__ command; scalar_t__ prot_version; } ;
struct qeth_ipa_cmd {TYPE_2__ hdr; } ;
struct qeth_cmd_buffer {int /*<<< orphan*/  channel; scalar_t__ data; } ;
struct TYPE_10__ {int buf_no; int /*<<< orphan*/  irq_pending; TYPE_5__* ccwdev; int /*<<< orphan*/  ccw; } ;
struct TYPE_7__ {int /*<<< orphan*/  ipa; } ;
struct qeth_card {scalar_t__ state; TYPE_4__ write; int /*<<< orphan*/  wait_q; int /*<<< orphan*/  lock; int /*<<< orphan*/  cmd_waiter_list; TYPE_1__ seqno; scalar_t__ read_or_write_problem; } ;
typedef  int /*<<< orphan*/  addr_t ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ CARD_STATE_DOWN ; 
 int /*<<< orphan*/  CTRL ; 
 int EIO ; 
 int ENOMEM ; 
 int ETIME ; 
 scalar_t__ IPA_CMD_SETIP ; 
 scalar_t__ IPA_PDU_HEADER_SIZE ; 
 scalar_t__ IS_IPA (scalar_t__) ; 
 int QETH_CMD_BUFFER_NO ; 
 int /*<<< orphan*/  QETH_DBF_CTRL_LEN ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 scalar_t__ QETH_IDX_COMMAND_SEQNO ; 
 unsigned long QETH_IPA_TIMEOUT ; 
 scalar_t__ QETH_PROT_IPV4 ; 
 unsigned long QETH_TIMEOUT ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ccw_device_start (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_ccwdev_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 struct qeth_reply* qeth_alloc_reply (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_prepare_control_data (struct qeth_card*,int,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_put_reply (struct qeth_reply*) ; 
 int /*<<< orphan*/  qeth_release_buffer (int /*<<< orphan*/ ,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int qeth_send_control_data(struct qeth_card *card, int len,
		struct qeth_cmd_buffer *iob,
		int (*reply_cb)(struct qeth_card *, struct qeth_reply *,
			unsigned long),
		void *reply_param)
{
	int rc;
	unsigned long flags;
	struct qeth_reply *reply = NULL;
	unsigned long timeout, event_timeout;
	struct qeth_ipa_cmd *cmd;

	QETH_DBF_TEXT(TRACE, 2, "sendctl");

	if (card->read_or_write_problem) {
		qeth_release_buffer(iob->channel, iob);
		return -EIO;
	}
	reply = qeth_alloc_reply(card);
	if (!reply) {
		return -ENOMEM;
	}
	reply->callback = reply_cb;
	reply->param = reply_param;
	if (card->state == CARD_STATE_DOWN)
		reply->seqno = QETH_IDX_COMMAND_SEQNO;
	else
		reply->seqno = card->seqno.ipa++;
	init_waitqueue_head(&reply->wait_q);
	spin_lock_irqsave(&card->lock, flags);
	list_add_tail(&reply->list, &card->cmd_waiter_list);
	spin_unlock_irqrestore(&card->lock, flags);
	QETH_DBF_HEX(CTRL, 2, iob->data, QETH_DBF_CTRL_LEN);

	while (atomic_cmpxchg(&card->write.irq_pending, 0, 1)) ;
	qeth_prepare_control_data(card, len, iob);

	if (IS_IPA(iob->data))
		event_timeout = QETH_IPA_TIMEOUT;
	else
		event_timeout = QETH_TIMEOUT;
	timeout = jiffies + event_timeout;

	QETH_DBF_TEXT(TRACE, 6, "noirqpnd");
	spin_lock_irqsave(get_ccwdev_lock(card->write.ccwdev), flags);
	rc = ccw_device_start(card->write.ccwdev, &card->write.ccw,
			      (addr_t) iob, 0, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(card->write.ccwdev), flags);
	if (rc) {
		QETH_DBF_MESSAGE(2, "%s qeth_send_control_data: "
			"ccw_device_start rc = %i\n",
			dev_name(&card->write.ccwdev->dev), rc);
		QETH_DBF_TEXT_(TRACE, 2, " err%d", rc);
		spin_lock_irqsave(&card->lock, flags);
		list_del_init(&reply->list);
		qeth_put_reply(reply);
		spin_unlock_irqrestore(&card->lock, flags);
		qeth_release_buffer(iob->channel, iob);
		atomic_set(&card->write.irq_pending, 0);
		wake_up(&card->wait_q);
		return rc;
	}

	/* we have only one long running ipassist, since we can ensure
	   process context of this command we can sleep */
	cmd = (struct qeth_ipa_cmd *)(iob->data+IPA_PDU_HEADER_SIZE);
	if ((cmd->hdr.command == IPA_CMD_SETIP) &&
	    (cmd->hdr.prot_version == QETH_PROT_IPV4)) {
		if (!wait_event_timeout(reply->wait_q,
		    atomic_read(&reply->received), event_timeout))
			goto time_err;
	} else {
		while (!atomic_read(&reply->received)) {
			if (time_after(jiffies, timeout))
				goto time_err;
			cpu_relax();
		};
	}

	if (reply->rc == -EIO)
		goto error;
	rc = reply->rc;
	qeth_put_reply(reply);
	return rc;

time_err:
	reply->rc = -ETIME;
	spin_lock_irqsave(&reply->card->lock, flags);
	list_del_init(&reply->list);
	spin_unlock_irqrestore(&reply->card->lock, flags);
	atomic_inc(&reply->received);
error:
	atomic_set(&card->write.irq_pending, 0);
	qeth_release_buffer(iob->channel, iob);
	card->write.buf_no = (card->write.buf_no + 1) % QETH_CMD_BUFFER_NO;
	rc = reply->rc;
	qeth_put_reply(reply);
	return rc;
}