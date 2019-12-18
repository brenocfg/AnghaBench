#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  opm; } ;
struct dasd_device {TYPE_2__* cdev; TYPE_1__ path_data; } ;
struct dasd_ccw_req {int /*<<< orphan*/  stopclk; int /*<<< orphan*/  status; int /*<<< orphan*/  lpm; int /*<<< orphan*/  flags; int /*<<< orphan*/  retries; struct dasd_device* startdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_CQR_FAILED ; 
 int /*<<< orphan*/  DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_VERIFY_PATH ; 
 int /*<<< orphan*/  DBF_DEBUG ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_clock () ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct dasd_ccw_req *
dasd_default_erp_action(struct dasd_ccw_req *cqr)
{
	struct dasd_device *device;

	device = cqr->startdev;

        /* just retry - there is nothing to save ... I got no sense data.... */
        if (cqr->retries > 0) {
		DBF_DEV_EVENT(DBF_DEBUG, device,
                             "default ERP called (%i retries left)",
                             cqr->retries);
		if (!test_bit(DASD_CQR_VERIFY_PATH, &cqr->flags))
			cqr->lpm = device->path_data.opm;
		cqr->status = DASD_CQR_FILLED;
        } else {
		pr_err("%s: default ERP has run out of retries and failed\n",
		       dev_name(&device->cdev->dev));
		cqr->status = DASD_CQR_FAILED;
		cqr->stopclk = get_clock();
        }
        return cqr;
}