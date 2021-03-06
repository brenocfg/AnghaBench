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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adp5520_bl {int /*<<< orphan*/  cached_daylight_max; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DAYLIGHT_MAX ; 
 int /*<<< orphan*/  adp5520_store (struct device*,char const*,size_t,int /*<<< orphan*/ ) ; 
 struct adp5520_bl* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  strict_strtoul (char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t adp5520_bl_daylight_max_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct adp5520_bl *data = dev_get_drvdata(dev);

	strict_strtoul(buf, 10, &data->cached_daylight_max);
	return adp5520_store(dev, buf, count, DAYLIGHT_MAX);
}