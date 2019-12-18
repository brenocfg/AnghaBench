#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct qeth_cmd_buffer {void (* callback ) (struct qeth_channel*,struct qeth_cmd_buffer*) ;TYPE_4__* data; } ;
struct TYPE_25__ {int count; scalar_t__ cda; } ;
struct qeth_channel {scalar_t__ state; TYPE_5__* ccwdev; int /*<<< orphan*/  irq_pending; TYPE_4__ ccw; } ;
struct TYPE_24__ {int func_level; int cula; int unit_addr2; scalar_t__ portno; } ;
struct TYPE_23__ {int issuer_rm_w; } ;
struct TYPE_22__ {int trans_hdr; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; TYPE_3__ info; TYPE_2__ token; TYPE_1__ seqno; struct qeth_channel write; } ;
struct ccw_dev_id {int devno; } ;
struct ccw1 {int dummy; } ;
typedef  int /*<<< orphan*/  addr_t ;
typedef  int __u8 ;
typedef  scalar_t__ __u32 ;
typedef  int __u16 ;
struct TYPE_26__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_DDEV (struct qeth_card*) ; 
 struct qeth_card* CARD_FROM_CDEV (TYPE_5__*) ; 
 scalar_t__ CH_STATE_ACTIVATING ; 
 int ERESTARTSYS ; 
 int ETIME ; 
 int* IDX_ACTIVATE_READ ; 
 int IDX_ACTIVATE_SIZE ; 
 int* IDX_ACTIVATE_WRITE ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 TYPE_4__* QETH_IDX_ACT_FUNC_LEVEL (TYPE_4__*) ; 
 TYPE_4__* QETH_IDX_ACT_ISSUER_RM_TOKEN (TYPE_4__*) ; 
 TYPE_4__* QETH_IDX_ACT_PNO (TYPE_4__*) ; 
 TYPE_4__* QETH_IDX_ACT_QDIO_DEV_CUA (TYPE_4__*) ; 
 TYPE_4__* QETH_IDX_ACT_QDIO_DEV_REALADDR (TYPE_4__*) ; 
 int QETH_MPC_TOKEN_LENGTH ; 
 int QETH_SEQ_NO_LENGTH ; 
 int /*<<< orphan*/  QETH_TIMEOUT ; 
 TYPE_4__* QETH_TRANSPORT_HEADER_SEQ_NO (TYPE_4__*) ; 
 int /*<<< orphan*/  SETUP ; 
 int* WRITE_CCW ; 
 scalar_t__ __pa (TYPE_4__*) ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_get_id (int /*<<< orphan*/ ,struct ccw_dev_id*) ; 
 int ccw_device_start (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  get_ccwdev_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,int*,int) ; 
 int /*<<< orphan*/  qeth_clear_cmd_buffers (struct qeth_channel*) ; 
 struct qeth_cmd_buffer* qeth_get_buffer (struct qeth_channel*) ; 
 int qeth_idx_activate_get_answer (struct qeth_channel*,void (*) (struct qeth_channel*,struct qeth_cmd_buffer*)) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_idx_activate_channel(struct qeth_channel *channel,
		void (*idx_reply_cb)(struct qeth_channel *,
			struct qeth_cmd_buffer *))
{
	struct qeth_card *card;
	struct qeth_cmd_buffer *iob;
	unsigned long flags;
	__u16 temp;
	__u8 tmp;
	int rc;
	struct ccw_dev_id temp_devid;

	card = CARD_FROM_CDEV(channel->ccwdev);

	QETH_DBF_TEXT(SETUP, 2, "idxactch");

	iob = qeth_get_buffer(channel);
	iob->callback = idx_reply_cb;
	memcpy(&channel->ccw, WRITE_CCW, sizeof(struct ccw1));
	channel->ccw.count = IDX_ACTIVATE_SIZE;
	channel->ccw.cda = (__u32) __pa(iob->data);
	if (channel == &card->write) {
		memcpy(iob->data, IDX_ACTIVATE_WRITE, IDX_ACTIVATE_SIZE);
		memcpy(QETH_TRANSPORT_HEADER_SEQ_NO(iob->data),
		       &card->seqno.trans_hdr, QETH_SEQ_NO_LENGTH);
		card->seqno.trans_hdr++;
	} else {
		memcpy(iob->data, IDX_ACTIVATE_READ, IDX_ACTIVATE_SIZE);
		memcpy(QETH_TRANSPORT_HEADER_SEQ_NO(iob->data),
		       &card->seqno.trans_hdr, QETH_SEQ_NO_LENGTH);
	}
	tmp = ((__u8)card->info.portno) | 0x80;
	memcpy(QETH_IDX_ACT_PNO(iob->data), &tmp, 1);
	memcpy(QETH_IDX_ACT_ISSUER_RM_TOKEN(iob->data),
	       &card->token.issuer_rm_w, QETH_MPC_TOKEN_LENGTH);
	memcpy(QETH_IDX_ACT_FUNC_LEVEL(iob->data),
	       &card->info.func_level, sizeof(__u16));
	ccw_device_get_id(CARD_DDEV(card), &temp_devid);
	memcpy(QETH_IDX_ACT_QDIO_DEV_CUA(iob->data), &temp_devid.devno, 2);
	temp = (card->info.cula << 8) + card->info.unit_addr2;
	memcpy(QETH_IDX_ACT_QDIO_DEV_REALADDR(iob->data), &temp, 2);

	wait_event(card->wait_q,
		   atomic_cmpxchg(&channel->irq_pending, 0, 1) == 0);
	QETH_DBF_TEXT(SETUP, 6, "noirqpnd");
	spin_lock_irqsave(get_ccwdev_lock(channel->ccwdev), flags);
	rc = ccw_device_start(channel->ccwdev,
			      &channel->ccw, (addr_t) iob, 0, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(channel->ccwdev), flags);

	if (rc) {
		QETH_DBF_MESSAGE(2, "Error1 in activating channel. rc=%d\n",
			rc);
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", rc);
		atomic_set(&channel->irq_pending, 0);
		wake_up(&card->wait_q);
		return rc;
	}
	rc = wait_event_interruptible_timeout(card->wait_q,
			channel->state == CH_STATE_ACTIVATING, QETH_TIMEOUT);
	if (rc == -ERESTARTSYS)
		return rc;
	if (channel->state != CH_STATE_ACTIVATING) {
		dev_warn(&channel->ccwdev->dev, "The qeth device driver"
			" failed to recover an error on the device\n");
		QETH_DBF_MESSAGE(2, "%s IDX activate timed out\n",
			dev_name(&channel->ccwdev->dev));
		QETH_DBF_TEXT_(SETUP, 2, "2err%d", -ETIME);
		qeth_clear_cmd_buffers(channel);
		return -ETIME;
	}
	return qeth_idx_activate_get_answer(channel, idx_reply_cb);
}