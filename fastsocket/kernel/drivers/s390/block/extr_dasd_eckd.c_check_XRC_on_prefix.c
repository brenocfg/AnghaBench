#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  XRC_supported; } ;
struct TYPE_7__ {TYPE_2__ facilities; } ;
struct dasd_eckd_private {TYPE_3__ rdc_data; } ;
struct dasd_device {scalar_t__ private; } ;
struct TYPE_8__ {int ga_extended; int /*<<< orphan*/  ep_sys_time; } ;
struct TYPE_5__ {int time_stamp; } ;
struct PFX_eckd_data {TYPE_4__ define_extent; TYPE_1__ validity; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOSYS ; 
 int get_sync_clock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_XRC_on_prefix(struct PFX_eckd_data *pfxdata,
			       struct dasd_device  *device)
{
	struct dasd_eckd_private *private;
	int rc;

	private = (struct dasd_eckd_private *) device->private;
	if (!private->rdc_data.facilities.XRC_supported)
		return 0;

	/* switch on System Time Stamp - needed for XRC Support */
	pfxdata->define_extent.ga_extended |= 0x08; /* 'Time Stamp Valid'   */
	pfxdata->define_extent.ga_extended |= 0x02; /* 'Extended Parameter' */
	pfxdata->validity.time_stamp = 1;	    /* 'Time Stamp Valid'   */

	rc = get_sync_clock(&pfxdata->define_extent.ep_sys_time);
	/* Ignore return code if sync clock is switched off. */
	if (rc == -ENOSYS || rc == -EACCES)
		rc = 0;
	return rc;
}