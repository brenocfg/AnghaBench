#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nand_chip {int /*<<< orphan*/  IO_ADDR_W; } ;
struct mtd_info {struct nand_chip* priv; } ;
struct TYPE_4__ {unsigned int data; } ;
typedef  TYPE_1__ reg_gio_rw_pa_dout ;

/* Variables and functions */
 int ALE_BIT ; 
 unsigned int CE_BIT ; 
 int CLE_BIT ; 
 unsigned int CTRL_BITMASK ; 
 unsigned int NAND_ALE ; 
 unsigned int NAND_CLE ; 
 int NAND_CMD_NONE ; 
 unsigned int NAND_CTRL_CHANGE ; 
 unsigned int NAND_NCE ; 
 unsigned int PIN_BITMASK ; 
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  gio ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  regi_gio ; 
 int /*<<< orphan*/  rw_pa_dout ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crisv32_hwcontrol(struct mtd_info *mtd, int cmd,
			      unsigned int ctrl)
{
	unsigned long flags;
	reg_gio_rw_pa_dout dout;
	struct nand_chip *this = mtd->priv;

	local_irq_save(flags);

	/* control bits change */
	if (ctrl & NAND_CTRL_CHANGE) {
		dout = REG_RD(gio, regi_gio, rw_pa_dout);
		dout.data &= ~PIN_BITMASK;

#if (CE_BIT == 4 && NAND_NCE == 1 &&  \
     CLE_BIT == 5 && NAND_CLE == 2 && \
     ALE_BIT == 6 && NAND_ALE == 4)
		/* Pins in same order as control bits, but shifted.
		 * Optimize for this case; works for 2.6.18 */
		dout.data |= ((ctrl & CTRL_BITMASK) ^ NAND_NCE) << CE_BIT;
#else
		/* the slow way */
		if (!(ctrl & NAND_NCE))
			dout.data |= (1 << CE_BIT);
		if (ctrl & NAND_CLE)
			dout.data |= (1 << CLE_BIT);
		if (ctrl & NAND_ALE)
			dout.data |= (1 << ALE_BIT);
#endif
		REG_WR(gio, regi_gio, rw_pa_dout, dout);
	}

	/* command to chip */
	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);

	local_irq_restore(flags);
}