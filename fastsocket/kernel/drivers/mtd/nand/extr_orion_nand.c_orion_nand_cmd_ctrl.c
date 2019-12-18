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
typedef  int u32 ;
struct orion_nand_data {int cle; int ale; } ;
struct nand_chip {int options; scalar_t__ IO_ADDR_W; struct orion_nand_data* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 int NAND_BUSWIDTH_16 ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void orion_nand_cmd_ctrl(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *nc = mtd->priv;
	struct orion_nand_data *board = nc->priv;
	u32 offs;

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		offs = (1 << board->cle);
	else if (ctrl & NAND_ALE)
		offs = (1 << board->ale);
	else
		return;

	if (nc->options & NAND_BUSWIDTH_16)
		offs <<= 1;

	writeb(cmd, nc->IO_ADDR_W + offs);
}