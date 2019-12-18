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
struct nand_chip {int /*<<< orphan*/  (* cmdfunc ) (struct mtd_info*,int /*<<< orphan*/ ,int,int) ;int /*<<< orphan*/  (* select_chip ) (struct mtd_info*,int) ;int /*<<< orphan*/  (* dev_ready ) (struct mtd_info*) ;} ;
struct mtd_info {struct nand_chip* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_DEPLETE1 ; 
 int /*<<< orphan*/  NAND_CMD_DEPLETE2 ; 
 int /*<<< orphan*/  stub1 (struct mtd_info*) ; 
 int /*<<< orphan*/  stub2 (struct mtd_info*,int) ; 
 int /*<<< orphan*/  stub3 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub4 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub5 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub6 (struct mtd_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void deplete(struct mtd_info *mtd, int chip)
{
	struct nand_chip *this = mtd->priv;

	/* wait until device is ready */
	while (!this->dev_ready(mtd)) ;

	this->select_chip(mtd, chip);

	/* Send the commands for device recovery, phase 1 */
	this->cmdfunc(mtd, NAND_CMD_DEPLETE1, 0x0000, 0x0000);
	this->cmdfunc(mtd, NAND_CMD_DEPLETE2, -1, -1);

	/* Send the commands for device recovery, phase 2 */
	this->cmdfunc(mtd, NAND_CMD_DEPLETE1, 0x0000, 0x0004);
	this->cmdfunc(mtd, NAND_CMD_DEPLETE2, -1, -1);

}