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
struct channel_info {int /*<<< orphan*/  sys_block_size; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned long) ; 
 struct channel_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  sscanf (char const*,char*,unsigned long*) ; 

__attribute__((used)) static ssize_t store_block_size(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct channel_info *channel = dev_get_drvdata(dev);
	unsigned long block_size;

	sscanf(buf, "%lu", &block_size);
	atomic_set(&channel->sys_block_size, block_size);

	return count;
}