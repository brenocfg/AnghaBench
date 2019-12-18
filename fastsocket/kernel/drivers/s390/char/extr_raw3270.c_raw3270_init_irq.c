#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct raw3270_view {TYPE_3__* dev; } ;
struct raw3270_request {int /*<<< orphan*/  rescnt; int /*<<< orphan*/  rc; } ;
struct TYPE_4__ {int dstat; int /*<<< orphan*/  count; } ;
struct TYPE_5__ {TYPE_1__ cmd; } ;
struct irb {int* ecw; TYPE_2__ scsw; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int DEV_STAT_ATTENTION ; 
 int DEV_STAT_UNIT_CHECK ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 int /*<<< orphan*/  RAW3270_FLAGS_ATTN ; 
 int /*<<< orphan*/  RAW3270_FLAGS_BUSY ; 
 int RAW3270_IO_BUSY ; 
 int RAW3270_IO_DONE ; 
 int SNS0_CMD_REJECT ; 
 int SNS0_INTERVENTION_REQ ; 
 int /*<<< orphan*/  raw3270_wait_queue ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
raw3270_init_irq(struct raw3270_view *view, struct raw3270_request *rq,
		 struct irb *irb)
{
	/*
	 * Unit-Check Processing:
	 * Expect Command Reject or Intervention Required.
	 */
	if (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) {
		/* Request finished abnormally. */
		if (irb->ecw[0] & SNS0_INTERVENTION_REQ) {
			set_bit(RAW3270_FLAGS_BUSY, &view->dev->flags);
			return RAW3270_IO_BUSY;
		}
	}
	if (rq) {
		if (irb->scsw.cmd.dstat & DEV_STAT_UNIT_CHECK) {
			if (irb->ecw[0] & SNS0_CMD_REJECT)
				rq->rc = -EOPNOTSUPP;
			else
				rq->rc = -EIO;
		} else
			/* Request finished normally. Copy residual count. */
			rq->rescnt = irb->scsw.cmd.count;
	}
	if (irb->scsw.cmd.dstat & DEV_STAT_ATTENTION) {
		set_bit(RAW3270_FLAGS_ATTN, &view->dev->flags);
		wake_up(&raw3270_wait_queue);
	}
	return RAW3270_IO_DONE;
}