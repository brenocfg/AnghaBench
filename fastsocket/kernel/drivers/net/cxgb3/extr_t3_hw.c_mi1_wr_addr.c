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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MI1_ADDR ; 
 int /*<<< orphan*/  A_MI1_CFG ; 
 int /*<<< orphan*/  A_MI1_DATA ; 
 int /*<<< orphan*/  A_MI1_OP ; 
 int /*<<< orphan*/  F_BUSY ; 
 int /*<<< orphan*/  MDIO_ATTEMPTS ; 
 int /*<<< orphan*/  M_ST ; 
 int V_MDI_OP (int /*<<< orphan*/ ) ; 
 int V_PHYADDR (int) ; 
 int V_REGADDR (int) ; 
 int /*<<< orphan*/  V_ST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_set_reg_field (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t3_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mi1_wr_addr(struct adapter *adapter, int phy_addr, int mmd_addr,
		       int reg_addr)
{
	u32 addr = V_REGADDR(mmd_addr) | V_PHYADDR(phy_addr);

	t3_set_reg_field(adapter, A_MI1_CFG, V_ST(M_ST), 0);
	t3_write_reg(adapter, A_MI1_ADDR, addr);
	t3_write_reg(adapter, A_MI1_DATA, reg_addr);
	t3_write_reg(adapter, A_MI1_OP, V_MDI_OP(0));
	return t3_wait_op_done(adapter, A_MI1_OP, F_BUSY, 0,
			       MDIO_ATTEMPTS, 10);
}