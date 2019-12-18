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
struct nand_chip {int /*<<< orphan*/  const* oob_poi; int /*<<< orphan*/  (* write_buf ) (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ;} ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; struct cafe_priv* priv; } ;
struct cafe_priv {int ctl2; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cafe_nand_write_page_lowlevel(struct mtd_info *mtd,
					  struct nand_chip *chip, const uint8_t *buf)
{
	struct cafe_priv *cafe = mtd->priv;

	chip->write_buf(mtd, buf, mtd->writesize);
	chip->write_buf(mtd, chip->oob_poi, mtd->oobsize);

	/* Set up ECC autogeneration */
	cafe->ctl2 |= (1<<30);
}