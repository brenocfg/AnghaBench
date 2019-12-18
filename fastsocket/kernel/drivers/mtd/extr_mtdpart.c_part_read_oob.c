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
struct mtd_part {scalar_t__ offset; TYPE_2__* master; } ;
struct mtd_oob_ops {scalar_t__ len; scalar_t__ datbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  failed; int /*<<< orphan*/  corrected; } ;
struct mtd_info {scalar_t__ size; TYPE_1__ ecc_stats; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {int (* read_oob ) (TYPE_2__*,scalar_t__,struct mtd_oob_ops*) ;} ;

/* Variables and functions */
 int EBADMSG ; 
 int EINVAL ; 
 int EUCLEAN ; 
 struct mtd_part* PART (struct mtd_info*) ; 
 int stub1 (TYPE_2__*,scalar_t__,struct mtd_oob_ops*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int part_read_oob(struct mtd_info *mtd, loff_t from,
		struct mtd_oob_ops *ops)
{
	struct mtd_part *part = PART(mtd);
	int res;

	if (from >= mtd->size)
		return -EINVAL;
	if (ops->datbuf && from + ops->len > mtd->size)
		return -EINVAL;
	res = part->master->read_oob(part->master, from + part->offset, ops);

	if (unlikely(res)) {
		if (res == -EUCLEAN)
			mtd->ecc_stats.corrected++;
		if (res == -EBADMSG)
			mtd->ecc_stats.failed++;
	}
	return res;
}