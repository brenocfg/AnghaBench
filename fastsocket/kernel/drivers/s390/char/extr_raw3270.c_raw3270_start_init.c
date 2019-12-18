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
struct raw3270_view {TYPE_1__* dev; } ;
struct raw3270_request {int rc; int /*<<< orphan*/ * callback_data; int /*<<< orphan*/ * callback; } ;
struct raw3270 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int __raw3270_start (struct raw3270*,struct raw3270_view*,struct raw3270_request*) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw3270_halt_io (TYPE_1__*,struct raw3270_request*) ; 
 scalar_t__ raw3270_registered ; 
 int /*<<< orphan*/  raw3270_request_final (struct raw3270_request*) ; 
 int /*<<< orphan*/  raw3270_wait_queue ; 
 int /*<<< orphan*/ * raw3270_wake_init ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_cons_dev () ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
raw3270_start_init(struct raw3270 *rp, struct raw3270_view *view,
		   struct raw3270_request *rq)
{
	unsigned long flags;
	int rc;

#ifdef CONFIG_TN3270_CONSOLE
	if (raw3270_registered == 0) {
		spin_lock_irqsave(get_ccwdev_lock(view->dev->cdev), flags);
		rq->callback = NULL;
		rc = __raw3270_start(rp, view, rq);
		if (rc == 0)
			while (!raw3270_request_final(rq)) {
				wait_cons_dev();
				barrier();
			}
		spin_unlock_irqrestore(get_ccwdev_lock(view->dev->cdev), flags);
		return rq->rc;
	}
#endif
	rq->callback = raw3270_wake_init;
	rq->callback_data = &raw3270_wait_queue;
	spin_lock_irqsave(get_ccwdev_lock(view->dev->cdev), flags);
	rc = __raw3270_start(rp, view, rq);
	spin_unlock_irqrestore(get_ccwdev_lock(view->dev->cdev), flags);
	if (rc)
		return rc;
	/* Now wait for the completion. */
	rc = wait_event_interruptible(raw3270_wait_queue,
				      raw3270_request_final(rq));
	if (rc == -ERESTARTSYS) {	/* Interrupted by a signal. */
		raw3270_halt_io(view->dev, rq);
		/* No wait for the halt to complete. */
		wait_event(raw3270_wait_queue, raw3270_request_final(rq));
		return -ERESTARTSYS;
	}
	return rq->rc;
}