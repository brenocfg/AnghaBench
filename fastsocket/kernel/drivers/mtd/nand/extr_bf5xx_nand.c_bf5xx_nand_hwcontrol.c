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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 int /*<<< orphan*/  SSYNC () ; 
 int WB_FULL ; 
 int bfin_read_NFC_STAT () ; 
 int /*<<< orphan*/  bfin_write_NFC_ADDR (int) ; 
 int /*<<< orphan*/  bfin_write_NFC_CMD (int) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void bf5xx_nand_hwcontrol(struct mtd_info *mtd, int cmd,
				   unsigned int ctrl)
{
	if (cmd == NAND_CMD_NONE)
		return;

	while (bfin_read_NFC_STAT() & WB_FULL)
		cpu_relax();

	if (ctrl & NAND_CLE)
		bfin_write_NFC_CMD(cmd);
	else
		bfin_write_NFC_ADDR(cmd);
	SSYNC();
}