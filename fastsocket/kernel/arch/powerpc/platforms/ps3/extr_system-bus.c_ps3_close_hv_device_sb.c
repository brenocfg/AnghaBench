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
struct ps3_system_bus_device {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  bus_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; scalar_t__ sb_12; scalar_t__ sb_11; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int lv1_close_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ps3_is_device (struct ps3_system_bus_device*,int,int) ; 
 TYPE_1__ usage_hack ; 

__attribute__((used)) static int ps3_close_hv_device_sb(struct ps3_system_bus_device *dev)
{
	int result;

	BUG_ON(!dev->bus_id);
	mutex_lock(&usage_hack.mutex);

	if (ps3_is_device(dev, 1, 1)) {
		usage_hack.sb_11--;
		if (usage_hack.sb_11) {
			result = 0;
			goto done;
		}
	}

	if (ps3_is_device(dev, 1, 2)) {
		usage_hack.sb_12--;
		if (usage_hack.sb_12) {
			result = 0;
			goto done;
		}
	}

	result = lv1_close_device(dev->bus_id, dev->dev_id);
	BUG_ON(result);

done:
	mutex_unlock(&usage_hack.mutex);
	return result;
}