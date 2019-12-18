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
struct TYPE_2__ {int /*<<< orphan*/  badblocks; } ;
struct mtd_info {int (* block_markbad ) (struct mtd_info*,scalar_t__) ;scalar_t__ size; TYPE_1__ ecc_stats; } ;
struct mtd_concat {int num_subdev; struct mtd_info** subdev; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 struct mtd_concat* CONCAT (struct mtd_info*) ; 
 int EINVAL ; 
 int stub1 (struct mtd_info*,scalar_t__) ; 

__attribute__((used)) static int concat_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct mtd_concat *concat = CONCAT(mtd);
	int i, err = -EINVAL;

	if (!concat->subdev[0]->block_markbad)
		return 0;

	if (ofs > mtd->size)
		return -EINVAL;

	for (i = 0; i < concat->num_subdev; i++) {
		struct mtd_info *subdev = concat->subdev[i];

		if (ofs >= subdev->size) {
			ofs -= subdev->size;
			continue;
		}

		err = subdev->block_markbad(subdev, ofs);
		if (!err)
			mtd->ecc_stats.badblocks++;
		break;
	}

	return err;
}