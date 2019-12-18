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
struct qeth_cmd_buffer {int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_pending; int /*<<< orphan*/  ccwdev; int /*<<< orphan*/  ccw; } ;
struct qeth_card {int /*<<< orphan*/  wait_q; TYPE_1__ write; } ;
typedef  int /*<<< orphan*/  addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_DBF_MESSAGE (int,char*,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ccw_device_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_prepare_control_data (struct qeth_card*,int,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  qeth_release_buffer (int /*<<< orphan*/ ,struct qeth_cmd_buffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_osn_send_control_data(struct qeth_card *card, int len,
			   struct qeth_cmd_buffer *iob)
{
	unsigned long flags;
	int rc = 0;

	QETH_DBF_TEXT(TRACE, 5, "osndctrd");

	wait_event(card->wait_q,
		   atomic_cmpxchg(&card->write.irq_pending, 0, 1) == 0);
	qeth_prepare_control_data(card, len, iob);
	QETH_DBF_TEXT(TRACE, 6, "osnoirqp");
	spin_lock_irqsave(get_ccwdev_lock(card->write.ccwdev), flags);
	rc = ccw_device_start(card->write.ccwdev, &card->write.ccw,
			      (addr_t) iob, 0, 0);
	spin_unlock_irqrestore(get_ccwdev_lock(card->write.ccwdev), flags);
	if (rc) {
		QETH_DBF_MESSAGE(2, "qeth_osn_send_control_data: "
			   "ccw_device_start rc = %i\n", rc);
		QETH_DBF_TEXT_(TRACE, 2, " err%d", rc);
		qeth_release_buffer(iob->channel, iob);
		atomic_set(&card->write.irq_pending, 0);
		wake_up(&card->wait_q);
	}
	return rc;
}