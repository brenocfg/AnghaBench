#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct mtd_oob_ops {int ooboffs; size_t ooblen; size_t oobretlen; int /*<<< orphan*/ * datbuf; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/  mode; } ;
struct mtd_info {int writesize; int (* write_oob ) (struct mtd_info*,int,struct mtd_oob_ops*) ;} ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OOB_PLACE ; 
 int stub1 (struct mtd_info*,int,struct mtd_oob_ops*) ; 

int nftl_write_oob(struct mtd_info *mtd, loff_t offs, size_t len,
		   size_t *retlen, uint8_t *buf)
{
	loff_t mask = mtd->writesize - 1;
	struct mtd_oob_ops ops;
	int res;

	ops.mode = MTD_OOB_PLACE;
	ops.ooboffs = offs & mask;
	ops.ooblen = len;
	ops.oobbuf = buf;
	ops.datbuf = NULL;

	res = mtd->write_oob(mtd, offs & ~mask, &ops);
	*retlen = ops.oobretlen;
	return res;
}