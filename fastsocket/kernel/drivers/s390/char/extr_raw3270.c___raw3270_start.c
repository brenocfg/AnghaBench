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
struct raw3270_view {int dummy; } ;
struct raw3270_request {int rc; int /*<<< orphan*/  list; int /*<<< orphan*/  ccw; struct raw3270_view* view; } ;
struct raw3270 {int /*<<< orphan*/  req_queue; int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAW3270_FLAGS_BUSY ; 
 int ccw_device_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw3270_get_view (struct raw3270_view*) ; 
 int /*<<< orphan*/  raw3270_put_view (struct raw3270_view*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__raw3270_start(struct raw3270 *rp, struct raw3270_view *view,
		struct raw3270_request *rq)
{
	rq->view = view;
	raw3270_get_view(view);
	if (list_empty(&rp->req_queue) &&
	    !test_bit(RAW3270_FLAGS_BUSY, &rp->flags)) {
		/* No other requests are on the queue. Start this one. */
		rq->rc = ccw_device_start(rp->cdev, &rq->ccw,
					       (unsigned long) rq, 0, 0);
		if (rq->rc) {
			raw3270_put_view(view);
			return rq->rc;
		}
	}
	list_add_tail(&rq->list, &rp->req_queue);
	return 0;
}