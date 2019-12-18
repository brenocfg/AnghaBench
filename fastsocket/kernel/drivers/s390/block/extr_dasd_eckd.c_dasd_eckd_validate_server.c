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
struct TYPE_2__ {scalar_t__ type; int /*<<< orphan*/  ssid; } ;
struct dasd_eckd_private {TYPE_1__ uid; } ;
struct dasd_device {int /*<<< orphan*/  cdev; scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DBF_WARNING ; 
 scalar_t__ MACHINE_IS_VM ; 
 scalar_t__ UA_BASE_PAV_ALIAS ; 
 scalar_t__ UA_HYPER_PAV_ALIAS ; 
 int dasd_eckd_psf_ssc (struct dasd_device*,int,unsigned long) ; 
 scalar_t__ dasd_nopav ; 

__attribute__((used)) static int dasd_eckd_validate_server(struct dasd_device *device,
				     unsigned long flags)
{
	int rc;
	struct dasd_eckd_private *private;
	int enable_pav;

	private = (struct dasd_eckd_private *) device->private;
	if (private->uid.type == UA_BASE_PAV_ALIAS ||
	    private->uid.type == UA_HYPER_PAV_ALIAS)
		return 0;
	if (dasd_nopav || MACHINE_IS_VM)
		enable_pav = 0;
	else
		enable_pav = 1;
	rc = dasd_eckd_psf_ssc(device, enable_pav, flags);

	/* may be requested feature is not available on server,
	 * therefore just report error and go ahead */
	DBF_EVENT_DEVID(DBF_WARNING, device->cdev, "PSF-SSC for SSID %04x "
			"returned rc=%d", private->uid.ssid, rc);
	return rc;
}