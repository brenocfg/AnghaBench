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
typedef  size_t u16 ;
struct scsi_device {int channel; scalar_t__ type; size_t id; TYPE_2__* host; } ;
struct megasas_instance {TYPE_1__* pd_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;
struct TYPE_3__ {scalar_t__ driveState; scalar_t__ driveType; } ;

/* Variables and functions */
 int ENXIO ; 
 int MEGASAS_MAX_DEV_PER_CHANNEL ; 
 int MEGASAS_MAX_PD_CHANNELS ; 
 scalar_t__ MR_PD_STATE_SYSTEM ; 
 scalar_t__ TYPE_DISK ; 
 struct megasas_instance* megasas_lookup_instance (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int megasas_slave_alloc(struct scsi_device *sdev)
{
	u16             pd_index = 0;
	struct megasas_instance *instance ;
	instance = megasas_lookup_instance(sdev->host->host_no);
	if ((sdev->channel < MEGASAS_MAX_PD_CHANNELS) &&
				(sdev->type == TYPE_DISK)) {
		/*
		 * Open the OS scan to the SYSTEM PD
		 */
		pd_index =
			(sdev->channel * MEGASAS_MAX_DEV_PER_CHANNEL) +
			sdev->id;
		if ((instance->pd_list[pd_index].driveState ==
					MR_PD_STATE_SYSTEM) &&
			(instance->pd_list[pd_index].driveType ==
						TYPE_DISK)) {
			return 0;
		}
		return -ENXIO;
	}
	return 0;
}