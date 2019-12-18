#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int size; int bytes; int (* correct ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_1__* layout; } ;
struct nand_chip {int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,scalar_t__,int) ;TYPE_2__ ecc; struct atmel_nand_host* priv; int /*<<< orphan*/ * oob_poi; } ;
struct TYPE_6__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {scalar_t__ writesize; int oobsize; TYPE_3__ ecc_stats; } ;
struct atmel_nand_host {int /*<<< orphan*/  ecc; } ;
struct TYPE_4__ {scalar_t__* eccpos; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_ECC_RST ; 
 int /*<<< orphan*/  CR ; 
 int /*<<< orphan*/  NAND_CMD_RNDOUT ; 
 scalar_t__ cpu_is_at32ap7000 () ; 
 int /*<<< orphan*/  ecc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int stub4 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (struct mtd_info*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub6 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int atmel_nand_read_page(struct mtd_info *mtd,
		struct nand_chip *chip, uint8_t *buf, int page)
{
	int eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	uint8_t *p = buf;
	uint8_t *oob = chip->oob_poi;
	uint8_t *ecc_pos;
	int stat;

	/*
	 * Errata: ALE is incorrectly wired up to the ECC controller
	 * on the AP7000, so it will include the address cycles in the
	 * ECC calculation.
	 *
	 * Workaround: Reset the parity registers before reading the
	 * actual data.
	 */
	if (cpu_is_at32ap7000()) {
		struct atmel_nand_host *host = chip->priv;
		ecc_writel(host->ecc, CR, ATMEL_ECC_RST);
	}

	/* read the page */
	chip->read_buf(mtd, p, eccsize);

	/* move to ECC position if needed */
	if (eccpos[0] != 0) {
		/* This only works on large pages
		 * because the ECC controller waits for
		 * NAND_CMD_RNDOUTSTART after the
		 * NAND_CMD_RNDOUT.
		 * anyway, for small pages, the eccpos[0] == 0
		 */
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT,
				mtd->writesize + eccpos[0], -1);
	}

	/* the ECC controller needs to read the ECC just after the data */
	ecc_pos = oob + eccpos[0];
	chip->read_buf(mtd, ecc_pos, eccbytes);

	/* check if there's an error */
	stat = chip->ecc.correct(mtd, p, oob, NULL);

	if (stat < 0)
		mtd->ecc_stats.failed++;
	else
		mtd->ecc_stats.corrected += stat;

	/* get back to oob start (end of page) */
	chip->cmdfunc(mtd, NAND_CMD_RNDOUT, mtd->writesize, -1);

	/* read the oob */
	chip->read_buf(mtd, oob, mtd->oobsize);

	return 0;
}