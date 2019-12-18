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
struct raw3270_request {int dummy; } ;
struct raw3270 {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int ccw_device_clear (int /*<<< orphan*/ ,long) ; 
 int ccw_device_halt (int /*<<< orphan*/ ,long) ; 
 scalar_t__ raw3270_request_final (struct raw3270_request*) ; 

__attribute__((used)) static int
raw3270_halt_io_nolock(struct raw3270 *rp, struct raw3270_request *rq)
{
	int retries;
	int rc;

	if (raw3270_request_final(rq))
		return 0;
	/* Check if interrupt has already been processed */
	for (retries = 0; retries < 5; retries++) {
		if (retries < 2)
			rc = ccw_device_halt(rp->cdev, (long) rq);
		else
			rc = ccw_device_clear(rp->cdev, (long) rq);
		if (rc == 0)
			break;		/* termination successful */
	}
	return rc;
}