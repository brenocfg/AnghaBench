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
struct dasd_ccw_req {int dummy; } ;

/* Variables and functions */
 struct dasd_ccw_req* dasd_3990_erp_add_erp (struct dasd_ccw_req*) ; 
 struct dasd_ccw_req* dasd_3990_erp_inspect (struct dasd_ccw_req*) ; 

__attribute__((used)) static struct dasd_ccw_req *
dasd_3990_erp_additional_erp(struct dasd_ccw_req * cqr)
{

	struct dasd_ccw_req *erp = NULL;

	/* add erp and initialize with default TIC */
	erp = dasd_3990_erp_add_erp(cqr);

	/* inspect sense, determine specific ERP if possible */
	if (erp != cqr) {

		erp = dasd_3990_erp_inspect(erp);
	}

	return erp;

}