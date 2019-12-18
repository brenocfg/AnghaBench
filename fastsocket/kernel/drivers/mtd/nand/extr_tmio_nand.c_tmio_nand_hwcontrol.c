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
typedef  int u8 ;
struct tmio_nand {scalar_t__ read_good; scalar_t__ fcr; } ;
struct nand_chip {scalar_t__ IO_ADDR_W; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 scalar_t__ FCR_MODE ; 
 int FCR_MODE_ALE ; 
 int FCR_MODE_CLE ; 
 int FCR_MODE_DATA ; 
 int FCR_MODE_STANDBY ; 
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_CTRL_CHANGE ; 
 unsigned int NAND_NCE ; 
 struct tmio_nand* mtd_to_tmio (struct mtd_info*) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int,scalar_t__) ; 

__attribute__((used)) static void tmio_nand_hwcontrol(struct mtd_info *mtd, int cmd,
				   unsigned int ctrl)
{
	struct tmio_nand *tmio = mtd_to_tmio(mtd);
	struct nand_chip *chip = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		u8 mode;

		if (ctrl & NAND_NCE) {
			mode = FCR_MODE_DATA;

			if (ctrl & NAND_CLE)
				mode |=  FCR_MODE_CLE;
			else
				mode &= ~FCR_MODE_CLE;

			if (ctrl & NAND_ALE)
				mode |=  FCR_MODE_ALE;
			else
				mode &= ~FCR_MODE_ALE;
		} else {
			mode = FCR_MODE_STANDBY;
		}

		tmio_iowrite8(mode, tmio->fcr + FCR_MODE);
		tmio->read_good = 0;
	}

	if (cmd != NAND_CMD_NONE)
		tmio_iowrite8(cmd, chip->IO_ADDR_W);
}