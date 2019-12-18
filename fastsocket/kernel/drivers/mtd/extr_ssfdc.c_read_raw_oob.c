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
struct mtd_oob_ops {scalar_t__ oobretlen; int /*<<< orphan*/ * datbuf; int /*<<< orphan*/ * oobbuf; scalar_t__ ooblen; scalar_t__ ooboffs; int /*<<< orphan*/  mode; } ;
struct mtd_info {int (* read_oob ) (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ;} ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTD_OOB_RAW ; 
 scalar_t__ OOB_SIZE ; 
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,struct mtd_oob_ops*) ; 

__attribute__((used)) static int read_raw_oob(struct mtd_info *mtd, loff_t offs, uint8_t *buf)
{
	struct mtd_oob_ops ops;
	int ret;

	ops.mode = MTD_OOB_RAW;
	ops.ooboffs = 0;
	ops.ooblen = OOB_SIZE;
	ops.oobbuf = buf;
	ops.datbuf = NULL;

	ret = mtd->read_oob(mtd, offs, &ops);
	if (ret < 0 || ops.oobretlen != OOB_SIZE)
		return -1;

	return 0;
}