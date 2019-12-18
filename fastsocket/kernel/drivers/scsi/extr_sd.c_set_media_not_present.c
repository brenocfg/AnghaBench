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
struct scsi_disk {TYPE_1__* device; scalar_t__ capacity; scalar_t__ media_present; } ;
struct TYPE_2__ {int changed; } ;

/* Variables and functions */

__attribute__((used)) static void set_media_not_present(struct scsi_disk *sdkp)
{
	sdkp->media_present = 0;
	sdkp->capacity = 0;
	sdkp->device->changed = 1;
}