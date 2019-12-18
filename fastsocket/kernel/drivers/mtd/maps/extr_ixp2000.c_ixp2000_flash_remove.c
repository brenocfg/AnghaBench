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
struct TYPE_4__ {struct flash_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_3__ {scalar_t__ map_priv_1; } ;
struct ixp2000_flash_info {scalar_t__ res; scalar_t__ partitions; TYPE_1__ map; scalar_t__ mtd; } ;
struct flash_platform_data {int /*<<< orphan*/  (* exit ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  del_mtd_partitions (scalar_t__) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  map_destroy (scalar_t__) ; 
 struct ixp2000_flash_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (scalar_t__) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int ixp2000_flash_remove(struct platform_device *dev)
{
	struct flash_platform_data *plat = dev->dev.platform_data;
	struct ixp2000_flash_info *info = platform_get_drvdata(dev);

	platform_set_drvdata(dev, NULL);

	if(!info)
		return 0;

	if (info->mtd) {
		del_mtd_partitions(info->mtd);
		map_destroy(info->mtd);
	}
	if (info->map.map_priv_1)
		iounmap((void *) info->map.map_priv_1);

	kfree(info->partitions);

	if (info->res) {
		release_resource(info->res);
		kfree(info->res);
	}

	if (plat->exit)
		plat->exit();

	return 0;
}