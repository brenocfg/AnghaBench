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
struct sys_device {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * cls; int /*<<< orphan*/  id; } ;
struct dma_info {TYPE_1__* pdev; } ;
struct dma_channel {int chan; int /*<<< orphan*/  vchan; struct sys_device dev; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_3__ {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  attr_config ; 
 int /*<<< orphan*/  attr_count ; 
 int /*<<< orphan*/  attr_dev_id ; 
 int /*<<< orphan*/  attr_flags ; 
 int /*<<< orphan*/  attr_mode ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dma_sysclass ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int sysdev_create_file (struct sys_device*,int /*<<< orphan*/ *) ; 
 int sysdev_register (struct sys_device*) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ unlikely (int) ; 

int dma_create_sysfs_files(struct dma_channel *chan, struct dma_info *info)
{
	struct sys_device *dev = &chan->dev;
	char name[16];
	int ret;

	dev->id  = chan->vchan;
	dev->cls = &dma_sysclass;

	ret = sysdev_register(dev);
	if (ret)
		return ret;

	ret |= sysdev_create_file(dev, &attr_dev_id);
	ret |= sysdev_create_file(dev, &attr_count);
	ret |= sysdev_create_file(dev, &attr_mode);
	ret |= sysdev_create_file(dev, &attr_flags);
	ret |= sysdev_create_file(dev, &attr_config);

	if (unlikely(ret)) {
		dev_err(&info->pdev->dev, "Failed creating attrs\n");
		return ret;
	}

	snprintf(name, sizeof(name), "dma%d", chan->chan);
	return sysfs_create_link(&info->pdev->dev.kobj, &dev->kobj, name);
}