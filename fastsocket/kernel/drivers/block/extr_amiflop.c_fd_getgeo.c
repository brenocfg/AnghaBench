#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hd_geometry {int sectors; int /*<<< orphan*/  cylinders; int /*<<< orphan*/  heads; } ;
struct block_device {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_6__ {TYPE_2__* type; TYPE_1__* dtype; } ;
struct TYPE_5__ {int sect_mult; int /*<<< orphan*/  tracks; int /*<<< orphan*/  heads; } ;
struct TYPE_4__ {int sects; } ;

/* Variables and functions */
 int MINOR (int /*<<< orphan*/ ) ; 
 TYPE_3__* unit ; 

__attribute__((used)) static int fd_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	int drive = MINOR(bdev->bd_dev) & 3;

	geo->heads = unit[drive].type->heads;
	geo->sectors = unit[drive].dtype->sects * unit[drive].type->sect_mult;
	geo->cylinders = unit[drive].type->tracks;
	return 0;
}