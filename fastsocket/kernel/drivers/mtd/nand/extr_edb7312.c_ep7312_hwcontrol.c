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
struct nand_chip {int /*<<< orphan*/  IO_ADDR_W; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_CTRL_CHANGE ; 
 unsigned int NAND_NCE ; 
 int clps_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clps_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ep7312_pxdr ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ep7312_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *chip = mtd->priv;

	if (ctrl & NAND_CTRL_CHANGE) {
		unsigned char bits = 0x80;

		bits |= (ctrl & (NAND_CLE | NAND_ALE)) << 3;
		bits |= (ctrl & NAND_NCE) ? 0x00 : 0x40;

		clps_writeb((clps_readb(ep7312_pxdr)  & 0xF0) | bits,
			    ep7312_pxdr);
	}
	if (cmd != NAND_CMD_NONE)
		writeb(cmd, chip->IO_ADDR_W);
}