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
struct TYPE_3__ {int /*<<< orphan*/  XRC_supported; } ;
struct TYPE_4__ {TYPE_1__ facilities; } ;
struct dasd_eckd_private {TYPE_2__ rdc_data; } ;
struct dasd_device {scalar_t__ private; } ;
struct ccw1 {int count; int /*<<< orphan*/  flags; } ;
struct DE_eckd_data {int ga_extended; int /*<<< orphan*/  ep_sys_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int EACCES ; 
 int ENOSYS ; 
 int get_sync_clock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
check_XRC (struct ccw1         *de_ccw,
           struct DE_eckd_data *data,
           struct dasd_device  *device)
{
        struct dasd_eckd_private *private;
	int rc;

        private = (struct dasd_eckd_private *) device->private;
	if (!private->rdc_data.facilities.XRC_supported)
		return 0;

        /* switch on System Time Stamp - needed for XRC Support */
	data->ga_extended |= 0x08; /* switch on 'Time Stamp Valid'   */
	data->ga_extended |= 0x02; /* switch on 'Extended Parameter' */

	rc = get_sync_clock(&data->ep_sys_time);
	/* Ignore return code if sync clock is switched off. */
	if (rc == -ENOSYS || rc == -EACCES)
		rc = 0;

	de_ccw->count = sizeof(struct DE_eckd_data);
	de_ccw->flags |= CCW_FLAG_SLI;
	return rc;
}