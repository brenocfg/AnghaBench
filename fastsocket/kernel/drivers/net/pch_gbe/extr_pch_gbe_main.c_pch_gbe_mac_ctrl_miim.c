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
typedef  int u32 ;
typedef  int u16 ;
struct pch_gbe_hw {int /*<<< orphan*/  miim_lock; TYPE_1__* reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  MIIM; } ;

/* Variables and functions */
 int PCH_GBE_MIIM_OPER_READ ; 
 int PCH_GBE_MIIM_OPER_READY ; 
 int PCH_GBE_MIIM_PHY_ADDR_SHIFT ; 
 int PCH_GBE_MIIM_REG_ADDR_SHIFT ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

u16 pch_gbe_mac_ctrl_miim(struct pch_gbe_hw *hw, u32 addr, u32 dir, u32 reg,
			u16 data)
{
	u32 data_out = 0;
	unsigned int i;
	unsigned long flags;

	spin_lock_irqsave(&hw->miim_lock, flags);

	for (i = 100; i; --i) {
		if ((ioread32(&hw->reg->MIIM) & PCH_GBE_MIIM_OPER_READY))
			break;
		udelay(20);
	}
	if (i == 0) {
		pr_err("pch-gbe.miim won't go Ready\n");
		spin_unlock_irqrestore(&hw->miim_lock, flags);
		return 0;	/* No way to indicate timeout error */
	}
	iowrite32(((reg << PCH_GBE_MIIM_REG_ADDR_SHIFT) |
		  (addr << PCH_GBE_MIIM_PHY_ADDR_SHIFT) |
		  dir | data), &hw->reg->MIIM);
	for (i = 0; i < 100; i++) {
		udelay(20);
		data_out = ioread32(&hw->reg->MIIM);
		if ((data_out & PCH_GBE_MIIM_OPER_READY))
			break;
	}
	spin_unlock_irqrestore(&hw->miim_lock, flags);

	pr_debug("PHY %s: reg=%d, data=0x%04X\n",
		 dir == PCH_GBE_MIIM_OPER_READ ? "READ" : "WRITE", reg,
		 dir == PCH_GBE_MIIM_OPER_READ ? data_out : data);
	return (u16) data_out;
}