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
typedef  int u16 ;
struct skge_hw {int phy_addr; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int PHY_RETRIES ; 
 int /*<<< orphan*/  XM_MMU_CMD ; 
 int XM_MMU_PHY_BUSY ; 
 int /*<<< orphan*/  XM_PHY_ADDR ; 
 int /*<<< orphan*/  XM_PHY_DATA ; 
 int /*<<< orphan*/  udelay (int) ; 
 int xm_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xm_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xm_phy_write(struct skge_hw *hw, int port, u16 reg, u16 val)
{
	int i;

	xm_write16(hw, port, XM_PHY_ADDR, reg | hw->phy_addr);
	for (i = 0; i < PHY_RETRIES; i++) {
		if (!(xm_read16(hw, port, XM_MMU_CMD) & XM_MMU_PHY_BUSY))
			goto ready;
		udelay(1);
	}
	return -EIO;

 ready:
	xm_write16(hw, port, XM_PHY_DATA, val);
	for (i = 0; i < PHY_RETRIES; i++) {
		if (!(xm_read16(hw, port, XM_MMU_CMD) & XM_MMU_PHY_BUSY))
			return 0;
		udelay(1);
	}
	return -ETIMEDOUT;
}