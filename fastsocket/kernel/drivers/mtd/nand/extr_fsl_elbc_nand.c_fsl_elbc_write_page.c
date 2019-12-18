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
struct nand_chip {int /*<<< orphan*/  const* oob_poi; struct fsl_elbc_mtd* priv; } ;
struct mtd_info {int /*<<< orphan*/  oobsize; int /*<<< orphan*/  writesize; } ;
struct fsl_elbc_mtd {struct fsl_elbc_ctrl* ctrl; } ;
struct fsl_elbc_ctrl {int /*<<< orphan*/  const* oob_poi; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsl_elbc_write_buf (struct mtd_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_elbc_write_page(struct mtd_info *mtd,
                                struct nand_chip *chip,
                                const uint8_t *buf)
{
	struct fsl_elbc_mtd *priv = chip->priv;
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;

	fsl_elbc_write_buf(mtd, buf, mtd->writesize);
	fsl_elbc_write_buf(mtd, chip->oob_poi, mtd->oobsize);

	ctrl->oob_poi = chip->oob_poi;
}