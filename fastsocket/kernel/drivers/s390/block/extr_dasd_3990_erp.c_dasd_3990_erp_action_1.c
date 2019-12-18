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
struct dasd_ccw_req {scalar_t__ status; int retries; struct dasd_ccw_req* (* function ) (struct dasd_ccw_req*) ;TYPE_2__* startdev; int /*<<< orphan*/  lpm; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  opm; } ;
struct TYPE_4__ {TYPE_1__ path_data; } ;

/* Variables and functions */
 scalar_t__ DASD_CQR_FAILED ; 
 scalar_t__ DASD_CQR_FILLED ; 
 int /*<<< orphan*/  DASD_CQR_VERIFY_PATH ; 
 struct dasd_ccw_req* dasd_3990_erp_action_1_sec (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  dasd_3990_erp_alternate_path (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct dasd_ccw_req *dasd_3990_erp_action_1(struct dasd_ccw_req *erp)
{
	erp->function = dasd_3990_erp_action_1;
	dasd_3990_erp_alternate_path(erp);
	if (erp->status == DASD_CQR_FAILED &&
	    !test_bit(DASD_CQR_VERIFY_PATH, &erp->flags)) {
		erp->status = DASD_CQR_FILLED;
		erp->retries = 10;
		erp->lpm = erp->startdev->path_data.opm;
		erp->function = dasd_3990_erp_action_1_sec;
	}
	return erp;
}