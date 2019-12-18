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
struct nand_chip {struct mxc_nand_host* priv; } ;
struct mxc_nand_host {int clk_act; int /*<<< orphan*/  clk; scalar_t__ regs; } ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  MTD_DEBUG_LEVEL0 ; 
 int NFC_CE ; 
 scalar_t__ NFC_CONFIG1 ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void mxc_nand_select_chip(struct mtd_info *mtd, int chip)
{
	struct nand_chip *nand_chip = mtd->priv;
	struct mxc_nand_host *host = nand_chip->priv;

#ifdef CONFIG_MTD_NAND_MXC_FORCE_CE
	if (chip > 0) {
		DEBUG(MTD_DEBUG_LEVEL0,
		      "ERROR:  Illegal chip select (chip = %d)\n", chip);
		return;
	}

	if (chip == -1) {
		writew(readw(host->regs + NFC_CONFIG1) & ~NFC_CE,
				host->regs + NFC_CONFIG1);
		return;
	}

	writew(readw(host->regs + NFC_CONFIG1) | NFC_CE,
			host->regs + NFC_CONFIG1);
#endif

	switch (chip) {
	case -1:
		/* Disable the NFC clock */
		if (host->clk_act) {
			clk_disable(host->clk);
			host->clk_act = 0;
		}
		break;
	case 0:
		/* Enable the NFC clock */
		if (!host->clk_act) {
			clk_enable(host->clk);
			host->clk_act = 1;
		}
		break;

	default:
		break;
	}
}