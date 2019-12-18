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
typedef  int /*<<< orphan*/  const uint8_t ;
struct TYPE_2__ {int size; int bytes; int steps; int prepad; int postpad; int /*<<< orphan*/  (* calculate ) (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* hwctl ) (struct mtd_info*,int /*<<< orphan*/ ) ;} ;
struct nand_chip {int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,int /*<<< orphan*/  const*,int) ;int /*<<< orphan*/  const* oob_poi; TYPE_1__ ecc; } ;
struct mtd_info {int oobsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_ECC_WRITE ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub5 (struct mtd_info*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub6 (struct mtd_info*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub7 (struct mtd_info*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void nand_write_page_syndrome(struct mtd_info *mtd,
				    struct nand_chip *chip, const uint8_t *buf)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	const uint8_t *p = buf;
	uint8_t *oob = chip->oob_poi;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {

		chip->ecc.hwctl(mtd, NAND_ECC_WRITE);
		chip->write_buf(mtd, p, eccsize);

		if (chip->ecc.prepad) {
			chip->write_buf(mtd, oob, chip->ecc.prepad);
			oob += chip->ecc.prepad;
		}

		chip->ecc.calculate(mtd, p, oob);
		chip->write_buf(mtd, oob, eccbytes);
		oob += eccbytes;

		if (chip->ecc.postpad) {
			chip->write_buf(mtd, oob, chip->ecc.postpad);
			oob += chip->ecc.postpad;
		}
	}

	/* Calculate remaining oob bytes */
	i = mtd->oobsize - (oob - chip->oob_poi);
	if (i)
		chip->write_buf(mtd, oob, i);
}