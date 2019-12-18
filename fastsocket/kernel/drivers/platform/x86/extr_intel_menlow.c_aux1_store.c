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
struct intel_menlow_attribute {int /*<<< orphan*/  handle; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CELSIUS_TO_KELVIN (int) ; 
 int EINVAL ; 
 int sensor_set_auxtrip (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,int*) ; 
 struct intel_menlow_attribute* to_intel_menlow_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t aux1_store(struct device *dev,
			  struct device_attribute *dev_attr,
			  const char *buf, size_t count)
{
	struct intel_menlow_attribute *attr = to_intel_menlow_attr(dev_attr);
	int value;
	int result;

	/*Sanity check; should be a positive integer */
	if (!sscanf(buf, "%d", &value))
		return -EINVAL;

	if (value < 0)
		return -EINVAL;

	result = sensor_set_auxtrip(attr->handle, 1, CELSIUS_TO_KELVIN(value));
	return result ? result : count;
}