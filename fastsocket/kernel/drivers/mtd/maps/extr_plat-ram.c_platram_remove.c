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
struct TYPE_2__ {int /*<<< orphan*/ * virt; } ;
struct platram_info {TYPE_1__ map; struct platram_info* area; scalar_t__ mtd; struct platram_info* partitions; scalar_t__ free_partitions; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATRAM_RO ; 
 int /*<<< orphan*/  del_mtd_device (scalar_t__) ; 
 int /*<<< orphan*/  del_mtd_partitions (scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct platram_info*) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platram_setrw (struct platram_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_resource (struct platram_info*) ; 
 struct platram_info* to_platram_info (struct platform_device*) ; 

__attribute__((used)) static int platram_remove(struct platform_device *pdev)
{
	struct platram_info *info = to_platram_info(pdev);

	platform_set_drvdata(pdev, NULL);

	dev_dbg(&pdev->dev, "removing device\n");

	if (info == NULL)
		return 0;

	if (info->mtd) {
#ifdef CONFIG_MTD_PARTITIONS
		if (info->partitions) {
			del_mtd_partitions(info->mtd);
			if (info->free_partitions)
				kfree(info->partitions);
		}
#endif
		del_mtd_device(info->mtd);
		map_destroy(info->mtd);
	}

	/* ensure ram is left read-only */

	platram_setrw(info, PLATRAM_RO);

	/* release resources */

	if (info->area) {
		release_resource(info->area);
		kfree(info->area);
	}

	if (info->map.virt != NULL)
		iounmap(info->map.virt);

	kfree(info);

	return 0;
}