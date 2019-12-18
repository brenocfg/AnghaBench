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
struct mtd_part {scalar_t__ offset; TYPE_1__* master; } ;
struct mtd_oob_ops {scalar_t__ len; scalar_t__ datbuf; } ;
struct mtd_info {int flags; scalar_t__ size; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int (* write_oob ) (TYPE_1__*,scalar_t__,struct mtd_oob_ops*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int EROFS ; 
 int MTD_WRITEABLE ; 
 struct mtd_part* PART (struct mtd_info*) ; 
 int stub1 (TYPE_1__*,scalar_t__,struct mtd_oob_ops*) ; 

__attribute__((used)) static int part_write_oob(struct mtd_info *mtd, loff_t to,
		struct mtd_oob_ops *ops)
{
	struct mtd_part *part = PART(mtd);

	if (!(mtd->flags & MTD_WRITEABLE))
		return -EROFS;

	if (to >= mtd->size)
		return -EINVAL;
	if (ops->datbuf && to + ops->len > mtd->size)
		return -EINVAL;
	return part->master->write_oob(part->master, to + part->offset, ops);
}