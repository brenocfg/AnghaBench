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
struct TYPE_2__ {int /*<<< orphan*/  (* write_page ) (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* write_page_raw ) (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*) ;} ;
struct nand_chip {int options; int (* waitfunc ) (struct mtd_info*,struct nand_chip*) ;int (* errstat ) (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int,int) ;scalar_t__ (* verify_buf ) (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;TYPE_1__ ecc; } ;
struct mtd_info {int /*<<< orphan*/  writesize; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FL_WRITING ; 
 int NAND_CACHEPRG ; 
 int /*<<< orphan*/  NAND_CMD_CACHEDPROG ; 
 int /*<<< orphan*/  NAND_CMD_PAGEPROG ; 
 int /*<<< orphan*/  NAND_CMD_READ0 ; 
 int /*<<< orphan*/  NAND_CMD_SEQIN ; 
 int NAND_STATUS_FAIL ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ stub10 (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int stub5 (struct mtd_info*,struct nand_chip*) ; 
 int stub6 (struct mtd_info*,struct nand_chip*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub7 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int stub8 (struct mtd_info*,struct nand_chip*) ; 
 int /*<<< orphan*/  stub9 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cafe_nand_write_page(struct mtd_info *mtd, struct nand_chip *chip,
				const uint8_t *buf, int page, int cached, int raw)
{
	int status;

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, 0x00, page);

	if (unlikely(raw))
		chip->ecc.write_page_raw(mtd, chip, buf);
	else
		chip->ecc.write_page(mtd, chip, buf);

	/*
	 * Cached progamming disabled for now, Not sure if its worth the
	 * trouble. The speed gain is not very impressive. (2.3->2.6Mib/s)
	 */
	cached = 0;

	if (!cached || !(chip->options & NAND_CACHEPRG)) {

		chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
		status = chip->waitfunc(mtd, chip);
		/*
		 * See if operation failed and additional status checks are
		 * available
		 */
		if ((status & NAND_STATUS_FAIL) && (chip->errstat))
			status = chip->errstat(mtd, chip, FL_WRITING, status,
					       page);

		if (status & NAND_STATUS_FAIL)
			return -EIO;
	} else {
		chip->cmdfunc(mtd, NAND_CMD_CACHEDPROG, -1, -1);
		status = chip->waitfunc(mtd, chip);
	}

#ifdef CONFIG_MTD_NAND_VERIFY_WRITE
	/* Send command to read back the data */
	chip->cmdfunc(mtd, NAND_CMD_READ0, 0, page);

	if (chip->verify_buf(mtd, buf, mtd->writesize))
		return -EIO;
#endif
	return 0;
}