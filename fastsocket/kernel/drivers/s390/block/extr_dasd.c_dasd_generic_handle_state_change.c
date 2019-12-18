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
struct dasd_device {scalar_t__ block; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_STOPPED_PENDING ; 
 int /*<<< orphan*/  dasd_device_remove_stop_bits (struct dasd_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_eer_snss (struct dasd_device*) ; 
 int /*<<< orphan*/  dasd_schedule_block_bh (scalar_t__) ; 
 int /*<<< orphan*/  dasd_schedule_device_bh (struct dasd_device*) ; 

void dasd_generic_handle_state_change(struct dasd_device *device)
{
	/* First of all start sense subsystem status request. */
	dasd_eer_snss(device);

	dasd_device_remove_stop_bits(device, DASD_STOPPED_PENDING);
	dasd_schedule_device_bh(device);
	if (device->block)
		dasd_schedule_block_bh(device->block);
}