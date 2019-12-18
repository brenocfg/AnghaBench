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
struct gendisk {int dummy; } ;
struct dasd_device {TYPE_2__* discipline; TYPE_1__* block; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;
struct TYPE_3__ {int /*<<< orphan*/  open_count; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct dasd_device* dasd_device_from_gendisk (struct gendisk*) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dasd_release(struct gendisk *disk, fmode_t mode)
{
	struct dasd_device *base;

	base = dasd_device_from_gendisk(disk);
	if (!base)
		return -ENODEV;

	atomic_dec(&base->block->open_count);
	module_put(base->discipline->owner);
	dasd_put_device(base);
	return 0;
}