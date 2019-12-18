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
typedef  void* u8 ;
struct TYPE_2__ {int /*<<< orphan*/  num_cyl; scalar_t__ num_sec; scalar_t__ num_hd; } ;
struct vdc_port {TYPE_1__ geom; } ;
struct hd_geometry {int /*<<< orphan*/  cylinders; void* sectors; void* heads; } ;
struct gendisk {struct vdc_port* private_data; } ;
struct block_device {struct gendisk* bd_disk; } ;

/* Variables and functions */

__attribute__((used)) static int vdc_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct gendisk *disk = bdev->bd_disk;
	struct vdc_port *port = disk->private_data;

	geo->heads = (u8) port->geom.num_hd;
	geo->sectors = (u8) port->geom.num_sec;
	geo->cylinders = port->geom.num_cyl;

	return 0;
}