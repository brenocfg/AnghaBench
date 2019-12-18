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
struct dasd_device {struct ccw_device* cdev; } ;
struct dasd_ccw_req {scalar_t__ startdev; } ;
struct TYPE_2__ {int cu_type; } ;
struct ccw_device {TYPE_1__ id; } ;
typedef  int /*<<< orphan*/  dasd_erp_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_3990_erp_action ; 
 int /*<<< orphan*/  dasd_default_erp_action ; 

__attribute__((used)) static dasd_erp_fn_t
dasd_eckd_erp_action(struct dasd_ccw_req * cqr)
{
	struct dasd_device *device = (struct dasd_device *) cqr->startdev;
	struct ccw_device *cdev = device->cdev;

	switch (cdev->id.cu_type) {
	case 0x3990:
	case 0x2105:
	case 0x2107:
	case 0x1750:
		return dasd_3990_erp_action;
	case 0x9343:
	case 0x3880:
	default:
		return dasd_default_erp_action;
	}
}