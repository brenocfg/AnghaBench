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
struct i2o_block_device {int power; int /*<<< orphan*/  i2o_dev; } ;
struct block_device {TYPE_1__* bd_disk; } ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_2__ {struct i2o_block_device* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  i2o_block_device_lock (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2o_block_device_mount (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2o_block_device_power (struct i2o_block_device*,int) ; 
 int /*<<< orphan*/  osm_debug (char*) ; 

__attribute__((used)) static int i2o_block_open(struct block_device *bdev, fmode_t mode)
{
	struct i2o_block_device *dev = bdev->bd_disk->private_data;

	if (!dev->i2o_dev)
		return -ENODEV;

	if (dev->power > 0x1f)
		i2o_block_device_power(dev, 0x02);

	i2o_block_device_mount(dev->i2o_dev, -1);

	i2o_block_device_lock(dev->i2o_dev, -1);

	osm_debug("Ready.\n");

	return 0;
}