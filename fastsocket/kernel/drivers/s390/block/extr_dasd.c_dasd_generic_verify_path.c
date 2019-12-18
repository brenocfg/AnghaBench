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
struct TYPE_2__ {int /*<<< orphan*/  opm; } ;
struct dasd_device {TYPE_1__ path_data; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  dasd_generic_path_operational (struct dasd_device*) ; 

int dasd_generic_verify_path(struct dasd_device *device, __u8 lpm)
{
	if (!device->path_data.opm && lpm) {
		device->path_data.opm = lpm;
		dasd_generic_path_operational(device);
	} else
		device->path_data.opm |= lpm;
	return 0;
}