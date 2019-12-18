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
struct raw3270_view {struct raw3270* dev; } ;
struct raw3270_request {int dummy; } ;
struct raw3270 {int /*<<< orphan*/  flags; struct raw3270_view* view; } ;

/* Variables and functions */
 int EACCES ; 
 int ENODEV ; 
 int /*<<< orphan*/  RAW3270_FLAGS_FROZEN ; 
 int /*<<< orphan*/  RAW3270_FLAGS_READY ; 
 int __raw3270_start (struct raw3270*,struct raw3270_view*,struct raw3270_request*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
raw3270_start_locked(struct raw3270_view *view, struct raw3270_request *rq)
{
	struct raw3270 *rp;
	int rc;

	rp = view->dev;
	if (!rp || rp->view != view ||
	    test_bit(RAW3270_FLAGS_FROZEN, &rp->flags))
		rc = -EACCES;
	else if (!test_bit(RAW3270_FLAGS_READY, &rp->flags))
		rc = -ENODEV;
	else
		rc =  __raw3270_start(rp, view, rq);
	return rc;
}