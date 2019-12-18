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
struct mtd_oob_ops {size_t len; scalar_t__ mode; size_t retlen; scalar_t__ ooboffs; int /*<<< orphan*/ * oobbuf; } ;
struct mtd_info {struct DiskOnChip* priv; } ;
struct Nand {scalar_t__ floor; scalar_t__ chip; } ;
struct DiskOnChip {size_t chipshift; scalar_t__ curfloor; scalar_t__ curchip; int /*<<< orphan*/  lock; scalar_t__ page256; struct Nand* chips; } ;
typedef  size_t loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_COLUMN_PAGE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CDSN_CTRL_WP ; 
 int /*<<< orphan*/  DoC_Address (struct DiskOnChip*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoC_Command (struct DiskOnChip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DoC_ReadBuf (struct DiskOnChip*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  DoC_SelectChip (struct DiskOnChip*,scalar_t__) ; 
 int /*<<< orphan*/  DoC_SelectFloor (struct DiskOnChip*,scalar_t__) ; 
 int DoC_WaitReady (struct DiskOnChip*) ; 
 scalar_t__ MTD_OOB_PLACE ; 
 int /*<<< orphan*/  NAND_CMD_READOOB ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int doc_read_oob(struct mtd_info *mtd, loff_t ofs,
			struct mtd_oob_ops *ops)
{
	struct DiskOnChip *this = mtd->priv;
	int len256 = 0, ret;
	struct Nand *mychip;
	uint8_t *buf = ops->oobbuf;
	size_t len = ops->len;

	BUG_ON(ops->mode != MTD_OOB_PLACE);

	ofs += ops->ooboffs;

	mutex_lock(&this->lock);

	mychip = &this->chips[ofs >> this->chipshift];

	if (this->curfloor != mychip->floor) {
		DoC_SelectFloor(this, mychip->floor);
		DoC_SelectChip(this, mychip->chip);
	} else if (this->curchip != mychip->chip) {
		DoC_SelectChip(this, mychip->chip);
	}
	this->curfloor = mychip->floor;
	this->curchip = mychip->chip;

	/* update address for 2M x 8bit devices. OOB starts on the second */
	/* page to maintain compatibility with doc_read_ecc. */
	if (this->page256) {
		if (!(ofs & 0x8))
			ofs += 0x100;
		else
			ofs -= 0x8;
	}

	DoC_Command(this, NAND_CMD_READOOB, CDSN_CTRL_WP);
	DoC_Address(this, ADDR_COLUMN_PAGE, ofs, CDSN_CTRL_WP, 0);

	/* treat crossing 8-byte OOB data for 2M x 8bit devices */
	/* Note: datasheet says it should automaticaly wrap to the */
	/*       next OOB block, but it didn't work here. mf.      */
	if (this->page256 && ofs + len > (ofs | 0x7) + 1) {
		len256 = (ofs | 0x7) + 1 - ofs;
		DoC_ReadBuf(this, buf, len256);

		DoC_Command(this, NAND_CMD_READOOB, CDSN_CTRL_WP);
		DoC_Address(this, ADDR_COLUMN_PAGE, ofs & (~0x1ff),
			    CDSN_CTRL_WP, 0);
	}

	DoC_ReadBuf(this, &buf[len256], len - len256);

	ops->retlen = len;
	/* Reading the full OOB data drops us off of the end of the page,
         * causing the flash device to go into busy mode, so we need
         * to wait until ready 11.4.1 and Toshiba TC58256FT docs */

	ret = DoC_WaitReady(this);

	mutex_unlock(&this->lock);
	return ret;

}