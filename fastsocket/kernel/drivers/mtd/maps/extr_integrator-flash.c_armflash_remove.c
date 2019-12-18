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
struct TYPE_3__ {struct flash_platform_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct flash_platform_data {int /*<<< orphan*/  (* exit ) () ;} ;
struct armflash_info {scalar_t__ mtd; int nr_subdev; TYPE_2__* subdev; struct armflash_info* parts; } ;
struct TYPE_4__ {scalar_t__ mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  armflash_subdev_remove (TYPE_2__*) ; 
 int /*<<< orphan*/  del_mtd_partitions (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct armflash_info*) ; 
 int /*<<< orphan*/  mtd_concat_destroy (scalar_t__) ; 
 struct armflash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int armflash_remove(struct platform_device *dev)
{
	struct armflash_info *info = platform_get_drvdata(dev);
	struct flash_platform_data *plat = dev->dev.platform_data;
	int i;

	platform_set_drvdata(dev, NULL);

	if (info) {
		if (info->mtd) {
			del_mtd_partitions(info->mtd);
#ifdef CONFIG_MTD_CONCAT
			if (info->mtd != info->subdev[0].mtd)
				mtd_concat_destroy(info->mtd);
#endif
		}
		kfree(info->parts);

		for (i = info->nr_subdev - 1; i >= 0; i--)
			armflash_subdev_remove(&info->subdev[i]);

		if (plat && plat->exit)
			plat->exit();

		kfree(info);
	}

	return 0;
}