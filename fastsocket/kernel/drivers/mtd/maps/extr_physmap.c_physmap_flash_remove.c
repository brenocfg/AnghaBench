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
struct TYPE_2__ {struct physmap_flash_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct physmap_flash_info {int /*<<< orphan*/ ** mtd; int /*<<< orphan*/ * cmtd; int /*<<< orphan*/  parts; scalar_t__ nr_parts; } ;
struct physmap_flash_data {scalar_t__ nr_parts; } ;

/* Variables and functions */
 int MAX_RESOURCES ; 
 int /*<<< orphan*/  del_mtd_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_mtd_partitions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtd_concat_destroy (int /*<<< orphan*/ *) ; 
 struct physmap_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int physmap_flash_remove(struct platform_device *dev)
{
	struct physmap_flash_info *info;
	struct physmap_flash_data *physmap_data;
	int i;

	info = platform_get_drvdata(dev);
	if (info == NULL)
		return 0;
	platform_set_drvdata(dev, NULL);

	physmap_data = dev->dev.platform_data;

	if (info->cmtd) {
#ifdef CONFIG_MTD_PARTITIONS
		if (info->nr_parts || physmap_data->nr_parts)
			del_mtd_partitions(info->cmtd);
		else
			del_mtd_device(info->cmtd);
#else
		del_mtd_device(info->cmtd);
#endif
	}
#ifdef CONFIG_MTD_PARTITIONS
	if (info->nr_parts)
		kfree(info->parts);
#endif

#ifdef CONFIG_MTD_CONCAT
	if (info->cmtd != info->mtd[0])
		mtd_concat_destroy(info->cmtd);
#endif

	for (i = 0; i < MAX_RESOURCES; i++) {
		if (info->mtd[i] != NULL)
			map_destroy(info->mtd[i]);
	}
	return 0;
}