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
struct sysdev_attribute {int dummy; } ;
struct sys_device {int dummy; } ;
struct dma_channel {int /*<<< orphan*/  mode; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dma_channel* to_dma_channel (struct sys_device*) ; 

__attribute__((used)) static ssize_t dma_store_mode(struct sys_device *dev,
			      struct sysdev_attribute *attr,
			      const char *buf, size_t count)
{
	struct dma_channel *channel = to_dma_channel(dev);
	channel->mode = simple_strtoul(buf, NULL, 0);
	return count;
}