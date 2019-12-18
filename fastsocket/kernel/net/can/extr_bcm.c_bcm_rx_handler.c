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
struct sk_buff {TYPE_1__* dev; int /*<<< orphan*/  tstamp; scalar_t__ data; } ;
struct can_frame {scalar_t__ can_id; } ;
struct bcm_op {scalar_t__ can_id; int flags; int nframes; struct can_frame const* frames; int /*<<< orphan*/ * last_frames; int /*<<< orphan*/  frames_abs; int /*<<< orphan*/  rx_ifindex; int /*<<< orphan*/  rx_stamp; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int GET_U64 (struct can_frame const*) ; 
 int RX_FILTER_ID ; 
 int RX_RTR_FRAME ; 
 int /*<<< orphan*/  bcm_can_tx (struct bcm_op*) ; 
 int /*<<< orphan*/  bcm_rx_cmp_to_index (struct bcm_op*,unsigned int,struct can_frame const*) ; 
 int /*<<< orphan*/  bcm_rx_starttimer (struct bcm_op*) ; 
 int /*<<< orphan*/  bcm_rx_update_and_send (struct bcm_op*,int /*<<< orphan*/ *,struct can_frame const*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm_rx_handler(struct sk_buff *skb, void *data)
{
	struct bcm_op *op = (struct bcm_op *)data;
	const struct can_frame *rxframe = (struct can_frame *)skb->data;
	unsigned int i;

	/* disable timeout */
	hrtimer_cancel(&op->timer);

	if (op->can_id != rxframe->can_id)
		return;

	/* save rx timestamp */
	op->rx_stamp = skb->tstamp;
	/* save originator for recvfrom() */
	op->rx_ifindex = skb->dev->ifindex;
	/* update statistics */
	op->frames_abs++;

	if (op->flags & RX_RTR_FRAME) {
		/* send reply for RTR-request (placed in op->frames[0]) */
		bcm_can_tx(op);
		return;
	}

	if (op->flags & RX_FILTER_ID) {
		/* the easiest case */
		bcm_rx_update_and_send(op, &op->last_frames[0], rxframe);
		goto rx_starttimer;
	}

	if (op->nframes == 1) {
		/* simple compare with index 0 */
		bcm_rx_cmp_to_index(op, 0, rxframe);
		goto rx_starttimer;
	}

	if (op->nframes > 1) {
		/*
		 * multiplex compare
		 *
		 * find the first multiplex mask that fits.
		 * Remark: The MUX-mask is stored in index 0
		 */

		for (i = 1; i < op->nframes; i++) {
			if ((GET_U64(&op->frames[0]) & GET_U64(rxframe)) ==
			    (GET_U64(&op->frames[0]) &
			     GET_U64(&op->frames[i]))) {
				bcm_rx_cmp_to_index(op, i, rxframe);
				break;
			}
		}
	}

rx_starttimer:
	bcm_rx_starttimer(op);
}