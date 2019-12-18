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
struct nand_chip {int options; int /*<<< orphan*/ * badblock_pattern; int /*<<< orphan*/ * bbt_md; int /*<<< orphan*/ * bbt_td; } ;
struct mtd_info {int writesize; struct nand_chip* priv; } ;

/* Variables and functions */
 int NAND_IS_AND ; 
 int NAND_USE_FLASH_BBT ; 
 int /*<<< orphan*/  agand_flashbased ; 
 int /*<<< orphan*/  bbt_main_descr ; 
 int /*<<< orphan*/  bbt_mirror_descr ; 
 int /*<<< orphan*/  largepage_flashbased ; 
 int /*<<< orphan*/  largepage_memorybased ; 
 int nand_scan_bbt (struct mtd_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smallpage_flashbased ; 
 int /*<<< orphan*/  smallpage_memorybased ; 

int nand_default_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = mtd->priv;

	/* Default for AG-AND. We must use a flash based
	 * bad block table as the devices have factory marked
	 * _good_ blocks. Erasing those blocks leads to loss
	 * of the good / bad information, so we _must_ store
	 * this information in a good / bad table during
	 * startup
	 */
	if (this->options & NAND_IS_AND) {
		/* Use the default pattern descriptors */
		if (!this->bbt_td) {
			this->bbt_td = &bbt_main_descr;
			this->bbt_md = &bbt_mirror_descr;
		}
		this->options |= NAND_USE_FLASH_BBT;
		return nand_scan_bbt(mtd, &agand_flashbased);
	}

	/* Is a flash based bad block table requested ? */
	if (this->options & NAND_USE_FLASH_BBT) {
		/* Use the default pattern descriptors */
		if (!this->bbt_td) {
			this->bbt_td = &bbt_main_descr;
			this->bbt_md = &bbt_mirror_descr;
		}
		if (!this->badblock_pattern) {
			this->badblock_pattern = (mtd->writesize > 512) ? &largepage_flashbased : &smallpage_flashbased;
		}
	} else {
		this->bbt_td = NULL;
		this->bbt_md = NULL;
		if (!this->badblock_pattern) {
			this->badblock_pattern = (mtd->writesize > 512) ?
			    &largepage_memorybased : &smallpage_memorybased;
		}
	}
	return nand_scan_bbt(mtd, this->badblock_pattern);
}