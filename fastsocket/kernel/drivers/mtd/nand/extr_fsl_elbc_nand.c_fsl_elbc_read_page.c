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
typedef  int /*<<< orphan*/  uint8_t ;
struct nand_chip {int /*<<< orphan*/ * oob_poi; } ;
struct TYPE_2__ {int /*<<< orphan*/  failed; } ;
struct mtd_info {TYPE_1__ ecc_stats; int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int NAND_STATUS_FAIL ; 
 int /*<<< orphan*/  fsl_elbc_read_buf (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int fsl_elbc_wait (struct mtd_info*,struct nand_chip*) ; 

__attribute__((used)) static int fsl_elbc_read_page(struct mtd_info *mtd,
                              struct nand_chip *chip,
			      uint8_t *buf,
			      int page)
{
	fsl_elbc_read_buf(mtd, buf, mtd->writesize);
	fsl_elbc_read_buf(mtd, chip->oob_poi, mtd->oobsize);

	if (fsl_elbc_wait(mtd, chip) & NAND_STATUS_FAIL)
		mtd->ecc_stats.failed++;

	return 0;
}