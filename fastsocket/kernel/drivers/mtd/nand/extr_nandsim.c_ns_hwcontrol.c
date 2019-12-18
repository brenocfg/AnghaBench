#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int cle; int ale; int ce; } ;
struct nandsim {TYPE_1__ lines; } ;
struct nand_chip {struct nandsim* priv; } ;
struct mtd_info {scalar_t__ priv; } ;

/* Variables and functions */
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_NCE ; 
 int /*<<< orphan*/  ns_nand_write_byte (struct mtd_info*,int) ; 

__attribute__((used)) static void ns_hwcontrol(struct mtd_info *mtd, int cmd, unsigned int bitmask)
{
	struct nandsim *ns = ((struct nand_chip *)mtd->priv)->priv;

	ns->lines.cle = bitmask & NAND_CLE ? 1 : 0;
	ns->lines.ale = bitmask & NAND_ALE ? 1 : 0;
	ns->lines.ce = bitmask & NAND_NCE ? 1 : 0;

	if (cmd != NAND_CMD_NONE)
		ns_nand_write_byte(mtd, cmd);
}