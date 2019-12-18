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
struct ap_device {int unregistered; int /*<<< orphan*/  qid; scalar_t__ pendingq_count; int /*<<< orphan*/  requestq_count; int /*<<< orphan*/  requestq; int /*<<< orphan*/  pendingq; scalar_t__ queue_count; int /*<<< orphan*/  reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_RESET_IGNORE ; 
 int ENODEV ; 
 int /*<<< orphan*/  __ap_schedule_poll_timer () ; 
 int ap_init_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ap_poll_requests ; 
 int /*<<< orphan*/  atomic_sub (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ap_reset(struct ap_device *ap_dev)
{
	int rc;

	ap_dev->reset = AP_RESET_IGNORE;
	atomic_sub(ap_dev->queue_count, &ap_poll_requests);
	ap_dev->queue_count = 0;
	list_splice_init(&ap_dev->pendingq, &ap_dev->requestq);
	ap_dev->requestq_count += ap_dev->pendingq_count;
	ap_dev->pendingq_count = 0;
	rc = ap_init_queue(ap_dev->qid);
	if (rc == -ENODEV)
		ap_dev->unregistered = 1;
	else
		__ap_schedule_poll_timer();
}