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
struct thermal_cooling_device {TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* set_cur_state ) (struct thermal_cooling_device*,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned long*) ; 
 int stub1 (struct thermal_cooling_device*,unsigned long) ; 
 struct thermal_cooling_device* to_cooling_device (struct device*) ; 

__attribute__((used)) static ssize_t
thermal_cooling_device_cur_state_store(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t count)
{
	struct thermal_cooling_device *cdev = to_cooling_device(dev);
	unsigned long state;
	int result;

	if (!sscanf(buf, "%ld\n", &state))
		return -EINVAL;

	if (state < 0)
		return -EINVAL;

	result = cdev->ops->set_cur_state(cdev, state);
	if (result)
		return result;
	return count;
}