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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int size; int bytes; int steps; int prepad; int (* correct ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int postpad; int /*<<< orphan*/  (* hwctl ) (struct mtd_info*,int /*<<< orphan*/ ) ;} ;
struct nand_chip {int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/ * oob_poi; TYPE_2__ ecc; } ;
struct TYPE_3__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {int oobsize; TYPE_1__ ecc_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ECC_READ ; 
 int /*<<< orphan*/  NAND_ECC_READSYN ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int stub6 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub7 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub8 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int nand_read_page_syndrome(struct mtd_info *mtd, struct nand_chip *chip,
				   uint8_t *buf, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *oob = chip->oob_poi;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		chip->ecc.hwctl(mtd, NAND_ECC_READ);
		chip->read_buf(mtd, p, eccsize);

		if (chip->ecc.prepad) {
			chip->read_buf(mtd, oob, chip->ecc.prepad);
			oob += chip->ecc.prepad;
		}

		chip->ecc.hwctl(mtd, NAND_ECC_READSYN);
		chip->read_buf(mtd, oob, eccbytes);
		stat = chip->ecc.correct(mtd, p, oob, NULL);

		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;

		oob += eccbytes;

		if (chip->ecc.postpad) {
			chip->read_buf(mtd, oob, chip->ecc.postpad);
			oob += chip->ecc.postpad;
		}
	}

	/* Calculate remaining oob bytes */
	i = mtd->oobsize - (oob - chip->oob_poi);
	if (i)
		chip->read_buf(mtd, oob, i);

	return 0;
}