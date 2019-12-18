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
struct TYPE_2__ {int class_id; } ;
struct i2o_device {int /*<<< orphan*/  device; TYPE_1__ lct_data; } ;

/* Variables and functions */
#define  I2O_CLASS_EXECUTIVE 129 
#define  I2O_CLASS_RANDOM_BLOCK_STORAGE 128 
 int /*<<< orphan*/  i2o_scsi_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void i2o_scsi_notify_device_remove(struct i2o_device *i2o_dev)
{
	switch (i2o_dev->lct_data.class_id) {
	case I2O_CLASS_EXECUTIVE:
	case I2O_CLASS_RANDOM_BLOCK_STORAGE:
		i2o_scsi_remove(&i2o_dev->device);
		break;

	default:
		break;
	}
}