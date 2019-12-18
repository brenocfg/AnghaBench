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
struct channel_info {int /*<<< orphan*/  sys_group_count; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned long) ; 
 struct channel_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned long*) ; 

__attribute__((used)) static ssize_t store_group_count(struct device *dev,
				struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct channel_info *channel = dev_get_drvdata(dev);
	unsigned long group_count;

	sscanf(buf, "%lu", &group_count);
	atomic_set(&channel->sys_group_count, group_count);

	return count;
}