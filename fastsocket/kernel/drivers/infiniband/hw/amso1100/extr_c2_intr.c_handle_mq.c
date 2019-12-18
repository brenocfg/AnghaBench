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
typedef  size_t u32 ;
struct c2_dev {int /*<<< orphan*/  req_vq_wo; int /*<<< orphan*/ ** qptr_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  c2_ae_event (struct c2_dev*,size_t) ; 
 int /*<<< orphan*/  c2_cq_event (struct c2_dev*,size_t) ; 
 int /*<<< orphan*/  handle_vq (struct c2_dev*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_mq(struct c2_dev *c2dev, u32 mq_index)
{
	if (c2dev->qptr_array[mq_index] == NULL) {
		pr_debug("handle_mq: stray activity for mq_index=%d\n",
			 mq_index);
		return;
	}

	switch (mq_index) {
	case (0):
		/*
		 * An index of 0 in the activity queue
		 * indicates the req vq now has messages
		 * available...
		 *
		 * Wake up any waiters waiting on req VQ
		 * message availability.
		 */
		wake_up(&c2dev->req_vq_wo);
		break;
	case (1):
		handle_vq(c2dev, mq_index);
		break;
	case (2):
		/* We have to purge the VQ in case there are pending
		 * accept reply requests that would result in the
		 * generation of an ESTABLISHED event. If we don't
		 * generate these first, a CLOSE event could end up
		 * being delivered before the ESTABLISHED event.
		 */
		handle_vq(c2dev, 1);

		c2_ae_event(c2dev, mq_index);
		break;
	default:
		/* There is no event synchronization between CQ events
		 * and AE or CM events. In fact, CQE could be
		 * delivered for all of the I/O up to and including the
		 * FLUSH for a peer disconenct prior to the ESTABLISHED
		 * event being delivered to the app. The reason for this
		 * is that CM events are delivered on a thread, while AE
		 * and CM events are delivered on interrupt context.
		 */
		c2_cq_event(c2dev, mq_index);
		break;
	}

	return;
}