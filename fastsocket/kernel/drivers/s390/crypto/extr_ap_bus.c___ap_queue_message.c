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
struct ap_queue_status {int response_code; } ;
struct ap_message {int /*<<< orphan*/  list; int /*<<< orphan*/  (* receive ) (struct ap_device*,struct ap_message*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  special; int /*<<< orphan*/  length; int /*<<< orphan*/  message; int /*<<< orphan*/  psmid; } ;
struct ap_device {scalar_t__ queue_count; scalar_t__ queue_depth; int /*<<< orphan*/  total_request_count; int /*<<< orphan*/  requestq_count; int /*<<< orphan*/  requestq; int /*<<< orphan*/  pendingq_count; int /*<<< orphan*/  pendingq; int /*<<< orphan*/  qid; } ;

/* Variables and functions */
#define  AP_RESPONSE_MESSAGE_TOO_BIG 132 
#define  AP_RESPONSE_NORMAL 131 
#define  AP_RESPONSE_Q_FULL 130 
#define  AP_RESPONSE_REQ_FAC_NOT_INST 129 
#define  AP_RESPONSE_RESET_IN_PROGRESS 128 
 int EBUSY ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  ERR_PTR (int) ; 
 struct ap_queue_status __ap_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_increase_queue_count (struct ap_device*) ; 
 int /*<<< orphan*/  ap_poll_requests ; 
 int /*<<< orphan*/  ap_schedule_poll_timer () ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ap_device*,struct ap_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ap_device*,struct ap_message*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ap_queue_message(struct ap_device *ap_dev, struct ap_message *ap_msg)
{
	struct ap_queue_status status;

	if (list_empty(&ap_dev->requestq) &&
	    ap_dev->queue_count < ap_dev->queue_depth) {
		status = __ap_send(ap_dev->qid, ap_msg->psmid,
				   ap_msg->message, ap_msg->length,
				   ap_msg->special);
		switch (status.response_code) {
		case AP_RESPONSE_NORMAL:
			list_add_tail(&ap_msg->list, &ap_dev->pendingq);
			atomic_inc(&ap_poll_requests);
			ap_dev->pendingq_count++;
			ap_increase_queue_count(ap_dev);
			ap_dev->total_request_count++;
			break;
		case AP_RESPONSE_Q_FULL:
		case AP_RESPONSE_RESET_IN_PROGRESS:
			list_add_tail(&ap_msg->list, &ap_dev->requestq);
			ap_dev->requestq_count++;
			ap_dev->total_request_count++;
			return -EBUSY;
		case AP_RESPONSE_REQ_FAC_NOT_INST:
		case AP_RESPONSE_MESSAGE_TOO_BIG:
			ap_msg->receive(ap_dev, ap_msg, ERR_PTR(-EINVAL));
			return -EINVAL;
		default:	/* Device is gone. */
			ap_msg->receive(ap_dev, ap_msg, ERR_PTR(-ENODEV));
			return -ENODEV;
		}
	} else {
		list_add_tail(&ap_msg->list, &ap_dev->requestq);
		ap_dev->requestq_count++;
		ap_dev->total_request_count++;
		return -EBUSY;
	}
	ap_schedule_poll_timer();
	return 0;
}