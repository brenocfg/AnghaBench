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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {struct fsl_elbc_mtd* priv; } ;
struct mtd_info {unsigned int writesize; unsigned int oobsize; struct nand_chip* priv; } ;
struct fsl_elbc_mtd {struct fsl_elbc_ctrl* ctrl; } ;
struct fsl_elbc_ctrl {unsigned int index; int /*<<< orphan*/ * addr; int /*<<< orphan*/  dev; scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void fsl_elbc_write_buf(struct mtd_info *mtd, const u8 *buf, int len)
{
	struct nand_chip *chip = mtd->priv;
	struct fsl_elbc_mtd *priv = chip->priv;
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;
	unsigned int bufsize = mtd->writesize + mtd->oobsize;

	if (len <= 0) {
		dev_err(ctrl->dev, "write_buf of %d bytes", len);
		ctrl->status = 0;
		return;
	}

	if ((unsigned int)len > bufsize - ctrl->index) {
		dev_err(ctrl->dev,
		        "write_buf beyond end of buffer "
		        "(%d requested, %u available)\n",
		        len, bufsize - ctrl->index);
		len = bufsize - ctrl->index;
	}

	memcpy_toio(&ctrl->addr[ctrl->index], buf, len);
	/*
	 * This is workaround for the weird elbc hangs during nand write,
	 * Scott Wood says: "...perhaps difference in how long it takes a
	 * write to make it through the localbus compared to a write to IMMR
	 * is causing problems, and sync isn't helping for some reason."
	 * Reading back the last byte helps though.
	 */
	in_8(&ctrl->addr[ctrl->index] + len - 1);

	ctrl->index += len;
}