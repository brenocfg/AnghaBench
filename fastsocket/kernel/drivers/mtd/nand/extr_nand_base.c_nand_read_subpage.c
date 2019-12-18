#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int size; int bytes; int (* correct ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* calculate ) (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;TYPE_1__* layout; } ;
struct nand_chip {int options; TYPE_3__* buffers; TYPE_2__ ecc; int /*<<< orphan*/ * oob_poi; int /*<<< orphan*/  (* read_buf ) (struct mtd_info*,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_8__ {int corrected; int /*<<< orphan*/  failed; } ;
struct mtd_info {int writesize; int oobsize; TYPE_4__ ecc_stats; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ecccalc; int /*<<< orphan*/ * ecccode; } ;
struct TYPE_5__ {int* eccpos; } ;

/* Variables and functions */
 int NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_CMD_RNDOUT ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub5 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub6 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub7 (struct mtd_info*,int /*<<< orphan*/ *,int) ; 
 int stub8 (struct mtd_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nand_read_subpage(struct mtd_info *mtd, struct nand_chip *chip, uint32_t data_offs, uint32_t readlen, uint8_t *bufpoi)
{
	int start_step, end_step, num_steps;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	uint8_t *p;
	int data_col_addr, i, gaps = 0;
	int datafrag_len, eccfrag_len, aligned_len, aligned_pos;
	int busw = (chip->options & NAND_BUSWIDTH_16) ? 2 : 1;

	/* Column address wihin the page aligned to ECC size (256bytes). */
	start_step = data_offs / chip->ecc.size;
	end_step = (data_offs + readlen - 1) / chip->ecc.size;
	num_steps = end_step - start_step + 1;

	/* Data size aligned to ECC ecc.size*/
	datafrag_len = num_steps * chip->ecc.size;
	eccfrag_len = num_steps * chip->ecc.bytes;

	data_col_addr = start_step * chip->ecc.size;
	/* If we read not a page aligned data */
	if (data_col_addr != 0)
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT, data_col_addr, -1);

	p = bufpoi + data_col_addr;
	chip->read_buf(mtd, p, datafrag_len);

	/* Calculate  ECC */
	for (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size)
		chip->ecc.calculate(mtd, p, &chip->buffers->ecccalc[i]);

	/* The performance is faster if to position offsets
	   according to ecc.pos. Let make sure here that
	   there are no gaps in ecc positions */
	for (i = 0; i < eccfrag_len - 1; i++) {
		if (eccpos[i + start_step * chip->ecc.bytes] + 1 !=
			eccpos[i + start_step * chip->ecc.bytes + 1]) {
			gaps = 1;
			break;
		}
	}
	if (gaps) {
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT, mtd->writesize, -1);
		chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
	} else {
		/* send the command to read the particular ecc bytes */
		/* take care about buswidth alignment in read_buf */
		aligned_pos = eccpos[start_step * chip->ecc.bytes] & ~(busw - 1);
		aligned_len = eccfrag_len;
		if (eccpos[start_step * chip->ecc.bytes] & (busw - 1))
			aligned_len++;
		if (eccpos[(start_step + num_steps) * chip->ecc.bytes] & (busw - 1))
			aligned_len++;

		chip->cmdfunc(mtd, NAND_CMD_RNDOUT, mtd->writesize + aligned_pos, -1);
		chip->read_buf(mtd, &chip->oob_poi[aligned_pos], aligned_len);
	}

	for (i = 0; i < eccfrag_len; i++)
		chip->buffers->ecccode[i] = chip->oob_poi[eccpos[i + start_step * chip->ecc.bytes]];

	p = bufpoi + data_col_addr;
	for (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size) {
		int stat;

		stat = chip->ecc.correct(mtd, p, &chip->buffers->ecccode[i], &chip->buffers->ecccalc[i]);
		if (stat == -1)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;
	}
	return 0;
}