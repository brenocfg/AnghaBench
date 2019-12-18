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
struct hpsa_scsi_dev_t {scalar_t__ raid_level; } ;

/* Variables and functions */

__attribute__((used)) static inline int device_updated(struct hpsa_scsi_dev_t *dev1,
	struct hpsa_scsi_dev_t *dev2)
{
	/* Device attributes that can change, but don't mean
	 * that the device is a different device, nor that the OS
	 * needs to be told anything about the change.
	 */
	if (dev1->raid_level != dev2->raid_level)
		return 1;
	return 0;
}