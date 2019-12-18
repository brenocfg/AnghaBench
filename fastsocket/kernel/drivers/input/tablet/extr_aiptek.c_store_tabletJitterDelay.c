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
struct TYPE_2__ {int jitterDelay; } ;
struct aiptek {TYPE_1__ newSetting; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 struct aiptek* dev_get_drvdata (struct device*) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 

__attribute__((used)) static ssize_t
store_tabletJitterDelay(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct aiptek *aiptek = dev_get_drvdata(dev);
	long j;

	if (strict_strtol(buf, 10, &j))
		return -EINVAL;

	aiptek->newSetting.jitterDelay = (int)j;
	return count;
}