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
struct mtd_oob_ops {int ooboffs; size_t len; size_t retlen; int /*<<< orphan*/ * datbuf; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/  ooblen; int /*<<< orphan*/  mode; } ;
struct mtd_info {int (* write_oob ) (struct mtd_info*,int,struct mtd_oob_ops*) ;int writesize; int /*<<< orphan*/  oobsize; } ;
typedef  int loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OOB_PLACE ; 
 int stub1 (struct mtd_info*,int,struct mtd_oob_ops*) ; 

__attribute__((used)) static int inftl_write(struct mtd_info *mtd, loff_t offs, size_t len,
		       size_t *retlen, uint8_t *buf, uint8_t *oob)
{
	struct mtd_oob_ops ops;
	int res;

	ops.mode = MTD_OOB_PLACE;
	ops.ooboffs = offs;
	ops.ooblen = mtd->oobsize;
	ops.oobbuf = oob;
	ops.datbuf = buf;
	ops.len = len;

	res = mtd->write_oob(mtd, offs & ~(mtd->writesize - 1), &ops);
	*retlen = ops.retlen;
	return res;
}