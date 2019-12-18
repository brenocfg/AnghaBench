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
typedef  int u16 ;
struct net_device {struct adapter* ml_priv; } ;
struct adapter {int /*<<< orphan*/  tpi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_PORT0_MI1_ADDR ; 
 int /*<<< orphan*/  A_ELMER0_PORT0_MI1_DATA ; 
 int /*<<< orphan*/  A_ELMER0_PORT0_MI1_OP ; 
 int MI1_OP_INDIRECT_ADDRESS ; 
 int MI1_OP_INDIRECT_WRITE ; 
 int V_MI1_PHY_ADDR (int) ; 
 int V_MI1_REG_ADDR (int) ; 
 int /*<<< orphan*/  __t1_tpi_write (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mi1_wait_until_ready (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mi1_mdio_ext_write(struct net_device *dev, int phy_addr,
			      int mmd_addr, u16 reg_addr, u16 val)
{
	struct adapter *adapter = dev->ml_priv;
	u32 addr = V_MI1_REG_ADDR(mmd_addr) | V_MI1_PHY_ADDR(phy_addr);

	spin_lock(&adapter->tpi_lock);

	/* Write the address we want. */
	__t1_tpi_write(adapter, A_ELMER0_PORT0_MI1_ADDR, addr);
	__t1_tpi_write(adapter, A_ELMER0_PORT0_MI1_DATA, reg_addr);
	__t1_tpi_write(adapter, A_ELMER0_PORT0_MI1_OP,
		       MI1_OP_INDIRECT_ADDRESS);
	mi1_wait_until_ready(adapter, A_ELMER0_PORT0_MI1_OP);

	/* Write the data. */
	__t1_tpi_write(adapter, A_ELMER0_PORT0_MI1_DATA, val);
	__t1_tpi_write(adapter, A_ELMER0_PORT0_MI1_OP, MI1_OP_INDIRECT_WRITE);
	mi1_wait_until_ready(adapter, A_ELMER0_PORT0_MI1_OP);
	spin_unlock(&adapter->tpi_lock);
	return 0;
}