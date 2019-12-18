#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct qeth_cmd_buffer {scalar_t__ state; int /*<<< orphan*/  (* callback ) (struct qeth_channel*,struct qeth_cmd_buffer*) ;} ;
struct qeth_channel {scalar_t__ state; size_t buf_no; struct qeth_cmd_buffer* iob; struct ccw_device* ccwdev; int /*<<< orphan*/  irq_pending; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; struct qeth_channel read; struct qeth_channel data; struct qeth_channel write; } ;
struct TYPE_8__ {scalar_t__ cons; } ;
struct TYPE_9__ {TYPE_3__ erw; } ;
struct TYPE_10__ {TYPE_4__ esw0; } ;
struct TYPE_6__ {int cstat; int dstat; int fctl; } ;
struct TYPE_7__ {TYPE_1__ cmd; } ;
struct irb {struct irb* ecw; TYPE_5__ esw; TYPE_2__ scsw; } ;
struct ccw_device {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  addr_t ;
typedef  size_t __u8 ;

/* Variables and functions */
 scalar_t__ BUF_STATE_PROCESSED ; 
 struct qeth_card* CARD_FROM_CDEV (struct ccw_device*) ; 
 scalar_t__ CH_STATE_DOWN ; 
 scalar_t__ CH_STATE_HALTED ; 
 scalar_t__ CH_STATE_RCD_DONE ; 
 scalar_t__ CH_STATE_STOPPED ; 
 scalar_t__ CH_STATE_UP ; 
 int DEV_STAT_UNIT_CHECK ; 
 int DEV_STAT_UNIT_EXCEP ; 
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 unsigned long QETH_CLEAR_CHANNEL_PARM ; 
 size_t QETH_CMD_BUFFER_NO ; 
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 unsigned long QETH_HALT_CHANNEL_PARM ; 
 unsigned long QETH_RCD_PARM ; 
 int SCSW_FCTL_CLEAR_FUNC ; 
 int SCSW_FCTL_HALT_FUNC ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ __qeth_check_irb_error (struct ccw_device*,unsigned long,struct irb*) ; 
 scalar_t__ __va (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,struct irb*,int,int) ; 
 int /*<<< orphan*/  qeth_clear_ipacmd_list (struct qeth_card*) ; 
 int qeth_get_problem (struct ccw_device*,struct irb*) ; 
 int /*<<< orphan*/  qeth_issue_next_read (struct qeth_card*) ; 
 int /*<<< orphan*/  qeth_schedule_recovery (struct qeth_card*) ; 
 int /*<<< orphan*/  stub1 (struct qeth_channel*,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qeth_irq(struct ccw_device *cdev, unsigned long intparm,
		struct irb *irb)
{
	int rc;
	int cstat, dstat;
	struct qeth_cmd_buffer *buffer;
	struct qeth_channel *channel;
	struct qeth_card *card;
	struct qeth_cmd_buffer *iob;
	__u8 index;

	QETH_DBF_TEXT(TRACE, 5, "irq");

	if (__qeth_check_irb_error(cdev, intparm, irb))
		return;
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	card = CARD_FROM_CDEV(cdev);
	if (!card)
		return;

	if (card->read.ccwdev == cdev) {
		channel = &card->read;
		QETH_DBF_TEXT(TRACE, 5, "read");
	} else if (card->write.ccwdev == cdev) {
		channel = &card->write;
		QETH_DBF_TEXT(TRACE, 5, "write");
	} else {
		channel = &card->data;
		QETH_DBF_TEXT(TRACE, 5, "data");
	}
	atomic_set(&channel->irq_pending, 0);

	if (irb->scsw.cmd.fctl & (SCSW_FCTL_CLEAR_FUNC))
		channel->state = CH_STATE_STOPPED;

	if (irb->scsw.cmd.fctl & (SCSW_FCTL_HALT_FUNC))
		channel->state = CH_STATE_HALTED;

	/*let's wake up immediately on data channel*/
	if ((channel == &card->data) && (intparm != 0) &&
	    (intparm != QETH_RCD_PARM))
		goto out;

	if (intparm == QETH_CLEAR_CHANNEL_PARM) {
		QETH_DBF_TEXT(TRACE, 6, "clrchpar");
		/* we don't have to handle this further */
		intparm = 0;
	}
	if (intparm == QETH_HALT_CHANNEL_PARM) {
		QETH_DBF_TEXT(TRACE, 6, "hltchpar");
		/* we don't have to handle this further */
		intparm = 0;
	}
	if ((dstat & DEV_STAT_UNIT_EXCEP) ||
	    (dstat & DEV_STAT_UNIT_CHECK) ||
	    (cstat)) {
		if (irb->esw.esw0.erw.cons) {
			dev_warn(&channel->ccwdev->dev,
				"The qeth device driver failed to recover "
				"an error on the device\n");
			QETH_DBF_MESSAGE(2, "%s sense data available. cstat "
				"0x%X dstat 0x%X\n",
				dev_name(&channel->ccwdev->dev), cstat, dstat);
			print_hex_dump(KERN_WARNING, "qeth: irb ",
				DUMP_PREFIX_OFFSET, 16, 1, irb, 32, 1);
			print_hex_dump(KERN_WARNING, "qeth: sense data ",
				DUMP_PREFIX_OFFSET, 16, 1, irb->ecw, 32, 1);
		}
		if (intparm == QETH_RCD_PARM) {
			channel->state = CH_STATE_DOWN;
			goto out;
		}
		rc = qeth_get_problem(cdev, irb);
		if (rc) {
			qeth_clear_ipacmd_list(card);
			qeth_schedule_recovery(card);
			goto out;
		}
	}

	if (intparm == QETH_RCD_PARM) {
		channel->state = CH_STATE_RCD_DONE;
		goto out;
	}
	if (intparm) {
		buffer = (struct qeth_cmd_buffer *) __va((addr_t)intparm);
		buffer->state = BUF_STATE_PROCESSED;
	}
	if (channel == &card->data)
		return;
	if (channel == &card->read &&
	    channel->state == CH_STATE_UP)
		qeth_issue_next_read(card);

	iob = channel->iob;
	index = channel->buf_no;
	while (iob[index].state == BUF_STATE_PROCESSED) {
		if (iob[index].callback != NULL)
			iob[index].callback(channel, iob + index);

		index = (index + 1) % QETH_CMD_BUFFER_NO;
	}
	channel->buf_no = index;
out:
	wake_up(&card->wait_q);
	return;
}