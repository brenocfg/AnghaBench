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
struct TYPE_3__ {int /*<<< orphan*/  tid; } ;
struct i2o_device {TYPE_1__ lct_data; } ;
struct i2o_block_device {TYPE_2__* gd; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_gendisk (TYPE_2__*) ; 
 struct i2o_block_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2o_block_device_free (struct i2o_block_device*) ; 
 int /*<<< orphan*/  i2o_block_driver ; 
 int /*<<< orphan*/  i2o_device_claim_release (struct i2o_device*) ; 
 int /*<<< orphan*/  i2o_event_register (struct i2o_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osm_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2o_device* to_i2o_device (struct device*) ; 

__attribute__((used)) static int i2o_block_remove(struct device *dev)
{
	struct i2o_device *i2o_dev = to_i2o_device(dev);
	struct i2o_block_device *i2o_blk_dev = dev_get_drvdata(dev);

	osm_info("device removed (TID: %03x): %s\n", i2o_dev->lct_data.tid,
		 i2o_blk_dev->gd->disk_name);

	i2o_event_register(i2o_dev, &i2o_block_driver, 0, 0);

	del_gendisk(i2o_blk_dev->gd);

	dev_set_drvdata(dev, NULL);

	i2o_device_claim_release(i2o_dev);

	i2o_block_device_free(i2o_blk_dev);

	return 0;
}