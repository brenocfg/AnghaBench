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
struct rbtx4939_flash_info {scalar_t__ mtd; int /*<<< orphan*/  parts; scalar_t__ nr_parts; } ;
struct rbtx4939_flash_data {scalar_t__ nr_parts; } ;
struct TYPE_2__ {struct rbtx4939_flash_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_mtd_device (scalar_t__) ; 
 int /*<<< orphan*/  del_mtd_partitions (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 struct rbtx4939_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rbtx4939_flash_remove(struct platform_device *dev)
{
	struct rbtx4939_flash_info *info;

	info = platform_get_drvdata(dev);
	if (!info)
		return 0;
	platform_set_drvdata(dev, NULL);

	if (info->mtd) {
#ifdef CONFIG_MTD_PARTITIONS
		struct rbtx4939_flash_data *pdata = dev->dev.platform_data;

		if (info->nr_parts) {
			del_mtd_partitions(info->mtd);
			kfree(info->parts);
		} else if (pdata->nr_parts)
			del_mtd_partitions(info->mtd);
		else
			del_mtd_device(info->mtd);
#else
		del_mtd_device(info->mtd);
#endif
		map_destroy(info->mtd);
	}
	return 0;
}