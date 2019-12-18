#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_device (struct device*) ; 
 scalar_t__ is_fw_device (struct device*) ; 
 int /*<<< orphan*/  set_broadcast_channel (int /*<<< orphan*/ ,long) ; 

int fw_device_set_broadcast_channel(struct device *dev, void *gen)
{
	if (is_fw_device(dev))
		set_broadcast_channel(fw_device(dev), (long)gen);

	return 0;
}