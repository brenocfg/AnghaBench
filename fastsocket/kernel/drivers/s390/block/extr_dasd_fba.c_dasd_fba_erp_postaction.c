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
struct dasd_ccw_req {scalar_t__ function; int /*<<< orphan*/  startdev; } ;
typedef  int /*<<< orphan*/ * dasd_erp_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 scalar_t__ dasd_default_erp_action ; 
 int /*<<< orphan*/ * dasd_default_erp_postaction ; 

__attribute__((used)) static dasd_erp_fn_t
dasd_fba_erp_postaction(struct dasd_ccw_req * cqr)
{
	if (cqr->function == dasd_default_erp_action)
		return dasd_default_erp_postaction;

	DBF_DEV_EVENT(DBF_WARNING, cqr->startdev, "unknown ERP action %p",
		    cqr->function);
	return NULL;
}