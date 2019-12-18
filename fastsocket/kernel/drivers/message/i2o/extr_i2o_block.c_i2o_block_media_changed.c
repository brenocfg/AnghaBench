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
struct i2o_block_device {scalar_t__ media_change_flag; } ;
struct gendisk {struct i2o_block_device* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int i2o_block_media_changed(struct gendisk *disk)
{
	struct i2o_block_device *p = disk->private_data;

	if (p->media_change_flag) {
		p->media_change_flag = 0;
		return 1;
	}
	return 0;
}