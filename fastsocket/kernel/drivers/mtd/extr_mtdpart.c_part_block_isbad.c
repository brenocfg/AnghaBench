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
struct mtd_part {TYPE_1__* master; scalar_t__ offset; } ;
struct mtd_info {int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int (* block_isbad ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct mtd_part* PART (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int part_block_isbad(struct mtd_info *mtd, loff_t ofs)
{
	struct mtd_part *part = PART(mtd);
	if (ofs >= mtd->size)
		return -EINVAL;
	ofs += part->offset;
	return part->master->block_isbad(part->master, ofs);
}