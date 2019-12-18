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
typedef  int /*<<< orphan*/  u_char ;
struct mtd_part {scalar_t__ offset; TYPE_2__* master; } ;
struct TYPE_3__ {int /*<<< orphan*/  failed; int /*<<< orphan*/  corrected; } ;
struct mtd_info {scalar_t__ size; TYPE_1__ ecc_stats; } ;
struct mtd_ecc_stats {scalar_t__ failed; scalar_t__ corrected; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {int (* read ) (TYPE_2__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/ *) ;struct mtd_ecc_stats ecc_stats; } ;

/* Variables and functions */
 int EBADMSG ; 
 int EUCLEAN ; 
 struct mtd_part* PART (struct mtd_info*) ; 
 int stub1 (TYPE_2__*,scalar_t__,size_t,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int part_read(struct mtd_info *mtd, loff_t from, size_t len,
		size_t *retlen, u_char *buf)
{
	struct mtd_part *part = PART(mtd);
	struct mtd_ecc_stats stats;
	int res;

	stats = part->master->ecc_stats;

	if (from >= mtd->size)
		len = 0;
	else if (from + len > mtd->size)
		len = mtd->size - from;
	res = part->master->read(part->master, from + part->offset,
				   len, retlen, buf);
	if (unlikely(res)) {
		if (res == -EUCLEAN)
			mtd->ecc_stats.corrected += part->master->ecc_stats.corrected - stats.corrected;
		if (res == -EBADMSG)
			mtd->ecc_stats.failed += part->master->ecc_stats.failed - stats.failed;
	}
	return res;
}