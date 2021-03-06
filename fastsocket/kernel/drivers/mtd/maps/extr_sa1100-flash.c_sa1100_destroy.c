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
struct sa_info {scalar_t__ mtd; scalar_t__ nr_parts; int num_subdev; TYPE_1__* subdev; struct sa_info* parts; } ;
struct flash_platform_data {int /*<<< orphan*/  (* exit ) () ;} ;
struct TYPE_2__ {scalar_t__ mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_mtd_device (scalar_t__) ; 
 int /*<<< orphan*/  del_mtd_partitions (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct sa_info*) ; 
 int /*<<< orphan*/  mtd_concat_destroy (scalar_t__) ; 
 int /*<<< orphan*/  sa1100_destroy_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void sa1100_destroy(struct sa_info *info, struct flash_platform_data *plat)
{
	int i;

	if (info->mtd) {
		if (info->nr_parts == 0)
			del_mtd_device(info->mtd);
#ifdef CONFIG_MTD_PARTITIONS
		else
			del_mtd_partitions(info->mtd);
#endif
#ifdef CONFIG_MTD_CONCAT
		if (info->mtd != info->subdev[0].mtd)
			mtd_concat_destroy(info->mtd);
#endif
	}

	kfree(info->parts);

	for (i = info->num_subdev - 1; i >= 0; i--)
		sa1100_destroy_subdev(&info->subdev[i]);
	kfree(info);

	if (plat->exit)
		plat->exit();
}