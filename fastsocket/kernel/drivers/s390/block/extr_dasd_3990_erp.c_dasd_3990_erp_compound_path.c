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
struct dasd_ccw_req {scalar_t__ status; void (* function ) (struct dasd_ccw_req*,char*) ;TYPE_2__* startdev; int /*<<< orphan*/  lpm; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  opm; } ;
struct TYPE_4__ {TYPE_1__ path_data; } ;

/* Variables and functions */
 scalar_t__ DASD_CQR_FAILED ; 
 scalar_t__ DASD_CQR_NEED_ERP ; 
 int /*<<< orphan*/  DASD_CQR_VERIFY_PATH ; 
 char DASD_SENSE_BIT_3 ; 
 int /*<<< orphan*/  dasd_3990_erp_alternate_path (struct dasd_ccw_req*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dasd_3990_erp_compound_path(struct dasd_ccw_req * erp, char *sense)
{
	if (sense[25] & DASD_SENSE_BIT_3) {
		dasd_3990_erp_alternate_path(erp);

		if (erp->status == DASD_CQR_FAILED &&
		    !test_bit(DASD_CQR_VERIFY_PATH, &erp->flags)) {
			/* reset the lpm and the status to be able to
			 * try further actions. */
			erp->lpm = erp->startdev->path_data.opm;
			erp->status = DASD_CQR_NEED_ERP;
		}
	}

	erp->function = dasd_3990_erp_compound_path;

}