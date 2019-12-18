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
struct dasd_device {int /*<<< orphan*/  ccw_queue; int /*<<< orphan*/  flags; struct dasd_ccw_req* eer_cqr; } ;
struct dasd_ccw_req {int /*<<< orphan*/  devlist; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_QUEUED ; 
 int /*<<< orphan*/  DASD_FLAG_EER_IN_USE ; 
 int /*<<< orphan*/  DASD_FLAG_EER_SNSS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void dasd_eer_snss(struct dasd_device *device)
{
	struct dasd_ccw_req *cqr;

	cqr = device->eer_cqr;
	if (!cqr)	/* Device not eer enabled. */
		return;
	if (test_and_set_bit(DASD_FLAG_EER_IN_USE, &device->flags)) {
		/* Sense subsystem status request in use. */
		set_bit(DASD_FLAG_EER_SNSS, &device->flags);
		return;
	}
	/* cdev is already locked, can't use dasd_add_request_head */
	clear_bit(DASD_FLAG_EER_SNSS, &device->flags);
	cqr->status = DASD_CQR_QUEUED;
	list_add(&cqr->devlist, &device->ccw_queue);
	dasd_schedule_device_bh(device);
}