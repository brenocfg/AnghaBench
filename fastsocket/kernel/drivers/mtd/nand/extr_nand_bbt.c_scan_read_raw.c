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
struct mtd_oob_ops {size_t len; int /*<<< orphan*/ * datbuf; int /*<<< orphan*/ * oobbuf; int /*<<< orphan*/  ooblen; scalar_t__ ooboffs; int /*<<< orphan*/  mode; } ;
struct mtd_info {int (* read_oob ) (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ;int /*<<< orphan*/  oobsize; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OOB_RAW ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int scan_read_raw(struct mtd_info *mtd, uint8_t *buf, loff_t offs,
			 size_t len)
{
	struct mtd_oob_ops ops;

	ops.mode = MTD_OOB_RAW;
	ops.ooboffs = 0;
	ops.ooblen = mtd->oobsize;
	ops.oobbuf = buf;
	ops.datbuf = buf;
	ops.len = len;

	return mtd->read_oob(mtd, offs, &ops);
}