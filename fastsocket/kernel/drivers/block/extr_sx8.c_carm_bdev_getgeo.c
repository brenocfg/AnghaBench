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
struct hd_geometry {int /*<<< orphan*/  cylinders; void* sectors; void* heads; } ;
struct carm_port {int /*<<< orphan*/  dev_geom_cyl; scalar_t__ dev_geom_sect; scalar_t__ dev_geom_head; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_2__ {struct carm_port* private_data; } ;

/* Variables and functions */

__attribute__((used)) static int carm_bdev_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	struct carm_port *port = bdev->bd_disk->private_data;

	geo->heads = (u8) port->dev_geom_head;
	geo->sectors = (u8) port->dev_geom_sect;
	geo->cylinders = port->dev_geom_cyl;
	return 0;
}