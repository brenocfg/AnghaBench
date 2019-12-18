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
struct TYPE_2__ {scalar_t__ tv64; } ;
struct bcm_op {scalar_t__ count; int flags; TYPE_1__ kt_ival2; int /*<<< orphan*/  timer; TYPE_1__ kt_ival1; int /*<<< orphan*/  can_id; int /*<<< orphan*/  ival2; int /*<<< orphan*/  ival1; } ;
struct bcm_msg_head {int flags; scalar_t__ count; scalar_t__ nframes; int /*<<< orphan*/  can_id; int /*<<< orphan*/  ival2; int /*<<< orphan*/  ival1; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int TX_COUNTEVT ; 
 int /*<<< orphan*/  TX_EXPIRED ; 
 int /*<<< orphan*/  bcm_can_tx (struct bcm_op*) ; 
 int /*<<< orphan*/  bcm_send_to_user (struct bcm_op*,struct bcm_msg_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void bcm_tx_timeout_tsklet(unsigned long data)
{
	struct bcm_op *op = (struct bcm_op *)data;
	struct bcm_msg_head msg_head;

	if (op->kt_ival1.tv64 && (op->count > 0)) {

		op->count--;
		if (!op->count && (op->flags & TX_COUNTEVT)) {

			/* create notification to user */
			msg_head.opcode  = TX_EXPIRED;
			msg_head.flags   = op->flags;
			msg_head.count   = op->count;
			msg_head.ival1   = op->ival1;
			msg_head.ival2   = op->ival2;
			msg_head.can_id  = op->can_id;
			msg_head.nframes = 0;

			bcm_send_to_user(op, &msg_head, NULL, 0);
		}
	}

	if (op->kt_ival1.tv64 && (op->count > 0)) {

		/* send (next) frame */
		bcm_can_tx(op);
		hrtimer_start(&op->timer,
			      ktime_add(ktime_get(), op->kt_ival1),
			      HRTIMER_MODE_ABS);

	} else {
		if (op->kt_ival2.tv64) {

			/* send (next) frame */
			bcm_can_tx(op);
			hrtimer_start(&op->timer,
				      ktime_add(ktime_get(), op->kt_ival2),
				      HRTIMER_MODE_ABS);
		}
	}
}