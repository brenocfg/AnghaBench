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
struct skge_hw {int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GM_SMI_CTRL ; 
 int GM_SMI_CT_OP_RD ; 
 int GM_SMI_CT_PHY_AD (int /*<<< orphan*/ ) ; 
 int GM_SMI_CT_RD_VAL ; 
 int GM_SMI_CT_REG_AD (int) ; 
 int /*<<< orphan*/  GM_SMI_DATA ; 
 int PHY_RETRIES ; 
 int gma_read16 (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gma_write16 (struct skge_hw*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int __gm_phy_read(struct skge_hw *hw, int port, u16 reg, u16 *val)
{
	int i;

	gma_write16(hw, port, GM_SMI_CTRL,
			 GM_SMI_CT_PHY_AD(hw->phy_addr)
			 | GM_SMI_CT_REG_AD(reg) | GM_SMI_CT_OP_RD);

	for (i = 0; i < PHY_RETRIES; i++) {
		udelay(1);
		if (gma_read16(hw, port, GM_SMI_CTRL) & GM_SMI_CT_RD_VAL)
			goto ready;
	}

	return -ETIMEDOUT;
 ready:
	*val = gma_read16(hw, port, GM_SMI_DATA);
	return 0;
}