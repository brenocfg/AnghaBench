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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int toolMode; } ;
struct aiptek {TYPE_1__ newSetting; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int AIPTEK_INVALID_VALUE ; 
 size_t EINVAL ; 
 struct aiptek* dev_get_drvdata (struct device*) ; 
 int map_str_to_val (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  tool_mode_map ; 

__attribute__((used)) static ssize_t
store_tabletToolMode(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);
	int new_mode = map_str_to_val(tool_mode_map, buf, count);

	if (new_mode == AIPTEK_INVALID_VALUE)
		return -EINVAL;

	aiptek->newSetting.toolMode = new_mode;
	return count;
}