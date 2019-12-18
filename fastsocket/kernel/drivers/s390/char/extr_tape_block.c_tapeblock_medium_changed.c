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
struct TYPE_2__ {int medium_changed; } ;
struct tape_device {TYPE_1__ blk_data; } ;
struct gendisk {scalar_t__ private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_LH (int,char*,struct tape_device*,int) ; 

__attribute__((used)) static int
tapeblock_medium_changed(struct gendisk *disk)
{
	struct tape_device *device;

	device = (struct tape_device *) disk->private_data;
	DBF_LH(6, "tapeblock_medium_changed(%p) = %d\n",
		device, device->blk_data.medium_changed);

	return device->blk_data.medium_changed;
}