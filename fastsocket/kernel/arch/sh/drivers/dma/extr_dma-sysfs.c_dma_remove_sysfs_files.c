#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sys_device {int dummy; } ;
struct dma_info {TYPE_2__* pdev; } ;
struct dma_channel {int chan; struct sys_device dev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_config ; 
 int /*<<< orphan*/  attr_count ; 
 int /*<<< orphan*/  attr_dev_id ; 
 int /*<<< orphan*/  attr_flags ; 
 int /*<<< orphan*/  attr_mode ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sysdev_remove_file (struct sys_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysdev_unregister (struct sys_device*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void dma_remove_sysfs_files(struct dma_channel *chan, struct dma_info *info)
{
	struct sys_device *dev = &chan->dev;
	char name[16];

	sysdev_remove_file(dev, &attr_dev_id);
	sysdev_remove_file(dev, &attr_count);
	sysdev_remove_file(dev, &attr_mode);
	sysdev_remove_file(dev, &attr_flags);
	sysdev_remove_file(dev, &attr_config);

	snprintf(name, sizeof(name), "dma%d", chan->chan);
	sysfs_remove_link(&info->pdev->dev.kobj, name);

	sysdev_unregister(dev);
}