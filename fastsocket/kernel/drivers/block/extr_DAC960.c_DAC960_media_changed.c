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
struct gendisk {scalar_t__ private_data; TYPE_1__* queue; } ;
struct TYPE_4__ {int /*<<< orphan*/ * LogicalDriveInitiallyAccessible; } ;
struct TYPE_3__ {TYPE_2__* queuedata; } ;
typedef  TYPE_2__ DAC960_Controller_T ;

/* Variables and functions */

__attribute__((used)) static int DAC960_media_changed(struct gendisk *disk)
{
	DAC960_Controller_T *p = disk->queue->queuedata;
	int drive_nr = (long)disk->private_data;

	if (!p->LogicalDriveInitiallyAccessible[drive_nr])
		return 1;
	return 0;
}