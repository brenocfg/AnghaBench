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
struct mtd_info {struct nand_chip* priv; } ;
struct fsl_elbc_mtd {struct fsl_elbc_ctrl* ctrl; } ;
struct fsl_elbc_ctrl {scalar_t__ index; scalar_t__ read_bytes; int /*<<< orphan*/  dev; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_BYTE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  in_8 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 fsl_elbc_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	struct fsl_elbc_mtd *priv = chip->priv;
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;

	/* If there are still bytes in the FCM, then use the next byte. */
	if (ctrl->index < ctrl->read_bytes)
		return in_8(&ctrl->addr[ctrl->index++]);

	dev_err(ctrl->dev, "read_byte beyond end of buffer\n");
	return ERR_BYTE;
}