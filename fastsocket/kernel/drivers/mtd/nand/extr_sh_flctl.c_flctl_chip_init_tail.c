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
struct TYPE_2__ {int size; int bytes; int /*<<< orphan*/  mode; int /*<<< orphan*/  write_page; int /*<<< orphan*/  read_page; int /*<<< orphan*/ * layout; } ;
struct nand_chip {int chipsize; TYPE_1__ ecc; int /*<<< orphan*/ * badblock_pattern; } ;
struct sh_flctl {int page_size; scalar_t__ hwecc; void* erase_ADRCNT; void* rw_ADRCNT; struct nand_chip chip; } ;
struct mtd_info {int writesize; } ;

/* Variables and functions */
 void* ADRCNT2_E ; 
 void* ADRCNT_1 ; 
 void* ADRCNT_2 ; 
 void* ADRCNT_3 ; 
 void* ADRCNT_4 ; 
 int ECCPOS2 ; 
 int ECCPOS_02 ; 
 int /*<<< orphan*/  FLCMNCR (struct sh_flctl*) ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  NAND_ECC_SOFT ; 
 int _4ECCEN ; 
 int /*<<< orphan*/  flctl_4secc_largepage ; 
 int /*<<< orphan*/  flctl_4secc_oob_16 ; 
 int /*<<< orphan*/  flctl_4secc_oob_64 ; 
 int /*<<< orphan*/  flctl_4secc_smallpage ; 
 int /*<<< orphan*/  flctl_read_page_hwecc ; 
 int /*<<< orphan*/  flctl_write_page_hwecc ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flctl_chip_init_tail(struct mtd_info *mtd)
{
	struct sh_flctl *flctl = mtd_to_flctl(mtd);
	struct nand_chip *chip = &flctl->chip;

	if (mtd->writesize == 512) {
		flctl->page_size = 0;
		if (chip->chipsize > (32 << 20)) {
			/* big than 32MB */
			flctl->rw_ADRCNT = ADRCNT_4;
			flctl->erase_ADRCNT = ADRCNT_3;
		} else if (chip->chipsize > (2 << 16)) {
			/* big than 128KB */
			flctl->rw_ADRCNT = ADRCNT_3;
			flctl->erase_ADRCNT = ADRCNT_2;
		} else {
			flctl->rw_ADRCNT = ADRCNT_2;
			flctl->erase_ADRCNT = ADRCNT_1;
		}
	} else {
		flctl->page_size = 1;
		if (chip->chipsize > (128 << 20)) {
			/* big than 128MB */
			flctl->rw_ADRCNT = ADRCNT2_E;
			flctl->erase_ADRCNT = ADRCNT_3;
		} else if (chip->chipsize > (8 << 16)) {
			/* big than 512KB */
			flctl->rw_ADRCNT = ADRCNT_4;
			flctl->erase_ADRCNT = ADRCNT_2;
		} else {
			flctl->rw_ADRCNT = ADRCNT_3;
			flctl->erase_ADRCNT = ADRCNT_1;
		}
	}

	if (flctl->hwecc) {
		if (mtd->writesize == 512) {
			chip->ecc.layout = &flctl_4secc_oob_16;
			chip->badblock_pattern = &flctl_4secc_smallpage;
		} else {
			chip->ecc.layout = &flctl_4secc_oob_64;
			chip->badblock_pattern = &flctl_4secc_largepage;
		}

		chip->ecc.size = 512;
		chip->ecc.bytes = 10;
		chip->ecc.read_page = flctl_read_page_hwecc;
		chip->ecc.write_page = flctl_write_page_hwecc;
		chip->ecc.mode = NAND_ECC_HW;

		/* 4 symbols ECC enabled */
		writel(readl(FLCMNCR(flctl)) | _4ECCEN | ECCPOS2 | ECCPOS_02,
				FLCMNCR(flctl));
	} else {
		chip->ecc.mode = NAND_ECC_SOFT;
	}

	return 0;
}