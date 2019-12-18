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
struct mspro_block_data {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors_per_track; int /*<<< orphan*/  heads; } ;
struct hd_geometry {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {struct mspro_block_data* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int mspro_block_bd_getgeo(struct block_device *bdev,
				 struct hd_geometry *geo)
{
	struct mspro_block_data *msb = bdev->bd_disk->private_data;

	geo->heads = msb->heads;
	geo->sectors = msb->sectors_per_track;
	geo->cylinders = msb->cylinders;

	return 0;
}