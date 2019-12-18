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
struct mtd_oob_ops {size_t len; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/ * datbuf; int /*<<< orphan*/  ooblen; scalar_t__ ooboffs; int /*<<< orphan*/  mode; } ;
struct mtd_info {int (* write_oob ) (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ;int /*<<< orphan*/  oobsize; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OOB_PLACE ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int scan_write_bbt(struct mtd_info *mtd, loff_t offs, size_t len,
			  uint8_t *buf, uint8_t *oob)
{
	struct mtd_oob_ops ops;

	ops.mode = MTD_OOB_PLACE;
	ops.ooboffs = 0;
	ops.ooblen = mtd->oobsize;
	ops.datbuf = buf;
	ops.oobbuf = oob;
	ops.len = len;

	return mtd->write_oob(mtd, offs, &ops);
}