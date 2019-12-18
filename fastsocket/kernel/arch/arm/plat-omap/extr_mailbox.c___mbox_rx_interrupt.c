#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct omap_mbox {TYPE_2__* rxq; TYPE_1__* ops; int /*<<< orphan*/  (* err_notify ) () ;} ;
typedef  scalar_t__ mbox_msg_t ;
struct TYPE_4__ {int /*<<< orphan*/  work; struct request_queue* queue; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IRQ_RX ; 
 scalar_t__ OMAP_MBOX_TYPE1 ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  ack_mbox_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 struct request* blk_get_request (struct request_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_insert_request (struct request_queue*,struct request*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  disable_mbox_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_mbox_irq (struct omap_mbox*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_fifo_empty (struct omap_mbox*) ; 
 scalar_t__ mbox_fifo_read (struct omap_mbox*) ; 
 int mbox_seq_test (struct omap_mbox*,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __mbox_rx_interrupt(struct omap_mbox *mbox)
{
	struct request *rq;
	mbox_msg_t msg;
	struct request_queue *q = mbox->rxq->queue;

	disable_mbox_irq(mbox, IRQ_RX);

	while (!mbox_fifo_empty(mbox)) {
		rq = blk_get_request(q, WRITE, GFP_ATOMIC);
		if (unlikely(!rq))
			goto nomem;

		msg = mbox_fifo_read(mbox);

		if (unlikely(mbox_seq_test(mbox, msg))) {
			pr_info("mbox: Illegal seq bit!(%08x)\n", msg);
			if (mbox->err_notify)
				mbox->err_notify();
		}

		blk_insert_request(q, rq, 0, (void *)msg);
		if (mbox->ops->type == OMAP_MBOX_TYPE1)
			break;
	}

	/* no more messages in the fifo. clear IRQ source. */
	ack_mbox_irq(mbox, IRQ_RX);
	enable_mbox_irq(mbox, IRQ_RX);
nomem:
	schedule_work(&mbox->rxq->work);
}