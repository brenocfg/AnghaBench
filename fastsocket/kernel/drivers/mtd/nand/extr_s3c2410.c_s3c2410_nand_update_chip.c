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
struct TYPE_2__ {scalar_t__ mode; int size; int bytes; int /*<<< orphan*/ * layout; } ;
struct nand_chip {int page_shift; TYPE_1__ ecc; } ;
struct s3c2410_nand_mtd {struct nand_chip chip; } ;
struct s3c2410_nand_info {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ NAND_ECC_HW ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct nand_chip*,int) ; 
 int /*<<< orphan*/  nand_hw_eccoob ; 

__attribute__((used)) static void s3c2410_nand_update_chip(struct s3c2410_nand_info *info,
				     struct s3c2410_nand_mtd *nmtd)
{
	struct nand_chip *chip = &nmtd->chip;

	dev_dbg(info->device, "chip %p => page shift %d\n",
		chip, chip->page_shift);

	if (chip->ecc.mode != NAND_ECC_HW)
		return;

		/* change the behaviour depending on wether we are using
		 * the large or small page nand device */

	if (chip->page_shift > 10) {
		chip->ecc.size	    = 256;
		chip->ecc.bytes	    = 3;
	} else {
		chip->ecc.size	    = 512;
		chip->ecc.bytes	    = 3;
		chip->ecc.layout    = &nand_hw_eccoob;
	}
}