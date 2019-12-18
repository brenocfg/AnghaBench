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
struct hd_i_struct {int /*<<< orphan*/  cyl; int /*<<< orphan*/  sect; int /*<<< orphan*/  head; } ;
struct hd_geometry {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {struct hd_i_struct* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int hd_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct hd_i_struct *disk = bdev->bd_disk->private_data;

	geo->heads = disk->head;
	geo->sectors = disk->sect;
	geo->cylinders = disk->cyl;
	return 0;
}