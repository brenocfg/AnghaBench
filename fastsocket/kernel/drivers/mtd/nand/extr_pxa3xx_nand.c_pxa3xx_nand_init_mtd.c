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
struct TYPE_2__ {int size; int /*<<< orphan*/ * layout; int /*<<< orphan*/  correct; int /*<<< orphan*/  calculate; int /*<<< orphan*/  hwctl; int /*<<< orphan*/  mode; } ;
struct nand_chip {int chip_delay; TYPE_1__ ecc; int /*<<< orphan*/  verify_buf; int /*<<< orphan*/  write_buf; int /*<<< orphan*/  read_buf; int /*<<< orphan*/  read_byte; int /*<<< orphan*/  read_word; int /*<<< orphan*/  cmdfunc; int /*<<< orphan*/  dev_ready; int /*<<< orphan*/  select_chip; int /*<<< orphan*/  waitfunc; int /*<<< orphan*/  options; } ;
struct pxa3xx_nand_info {struct nand_chip nand_chip; struct pxa3xx_nand_flash* flash_info; } ;
struct pxa3xx_nand_flash {int flash_width; int page_size; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_BUSWIDTH_16 ; 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  hw_largepage_ecclayout ; 
 int /*<<< orphan*/  hw_smallpage_ecclayout ; 
 int /*<<< orphan*/  pxa3xx_nand_cmdfunc ; 
 int /*<<< orphan*/  pxa3xx_nand_dev_ready ; 
 int /*<<< orphan*/  pxa3xx_nand_ecc_calculate ; 
 int /*<<< orphan*/  pxa3xx_nand_ecc_correct ; 
 int /*<<< orphan*/  pxa3xx_nand_ecc_hwctl ; 
 int /*<<< orphan*/  pxa3xx_nand_read_buf ; 
 int /*<<< orphan*/  pxa3xx_nand_read_byte ; 
 int /*<<< orphan*/  pxa3xx_nand_read_word ; 
 int /*<<< orphan*/  pxa3xx_nand_select_chip ; 
 int /*<<< orphan*/  pxa3xx_nand_verify_buf ; 
 int /*<<< orphan*/  pxa3xx_nand_waitfunc ; 
 int /*<<< orphan*/  pxa3xx_nand_write_buf ; 

__attribute__((used)) static void pxa3xx_nand_init_mtd(struct mtd_info *mtd,
				 struct pxa3xx_nand_info *info)
{
	const struct pxa3xx_nand_flash *f = info->flash_info;
	struct nand_chip *this = &info->nand_chip;

	this->options = (f->flash_width == 16) ? NAND_BUSWIDTH_16: 0;

	this->waitfunc		= pxa3xx_nand_waitfunc;
	this->select_chip	= pxa3xx_nand_select_chip;
	this->dev_ready		= pxa3xx_nand_dev_ready;
	this->cmdfunc		= pxa3xx_nand_cmdfunc;
	this->read_word		= pxa3xx_nand_read_word;
	this->read_byte		= pxa3xx_nand_read_byte;
	this->read_buf		= pxa3xx_nand_read_buf;
	this->write_buf		= pxa3xx_nand_write_buf;
	this->verify_buf	= pxa3xx_nand_verify_buf;

	this->ecc.mode		= NAND_ECC_HW;
	this->ecc.hwctl		= pxa3xx_nand_ecc_hwctl;
	this->ecc.calculate	= pxa3xx_nand_ecc_calculate;
	this->ecc.correct	= pxa3xx_nand_ecc_correct;
	this->ecc.size		= f->page_size;

	if (f->page_size == 2048)
		this->ecc.layout = &hw_largepage_ecclayout;
	else
		this->ecc.layout = &hw_smallpage_ecclayout;

	this->chip_delay = 25;
}