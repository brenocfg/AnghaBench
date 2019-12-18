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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct ixgbe_hw {int revision_id; int device_id; } ;
struct ixgbevf_adapter {struct ixgbe_hw hw; } ;
struct ethtool_regs {int version; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VFCTRL ; 
 int /*<<< orphan*/  IXGBE_VFFRTIMER ; 
 int /*<<< orphan*/  IXGBE_VFLINKS ; 
 int /*<<< orphan*/  IXGBE_VFPSRTYPE ; 
 int /*<<< orphan*/  IXGBE_VFRDBAH (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDBAL (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDH (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDLEN (int) ; 
 int /*<<< orphan*/  IXGBE_VFRDT (int) ; 
 int /*<<< orphan*/  IXGBE_VFRXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_VFRXMEMWRAP ; 
 int /*<<< orphan*/  IXGBE_VFSRRCTL (int) ; 
 int /*<<< orphan*/  IXGBE_VFSTATUS ; 
 int /*<<< orphan*/  IXGBE_VFTDBAH (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDBAL (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDH (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDLEN (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDT (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDWBAH (int) ; 
 int /*<<< orphan*/  IXGBE_VFTDWBAL (int) ; 
 int /*<<< orphan*/  IXGBE_VFTXDCTL (int) ; 
 int /*<<< orphan*/  IXGBE_VTEIAC ; 
 int /*<<< orphan*/  IXGBE_VTEIAM ; 
 int /*<<< orphan*/  IXGBE_VTEICS ; 
 int /*<<< orphan*/  IXGBE_VTEIMC ; 
 int /*<<< orphan*/  IXGBE_VTEIMS ; 
 int /*<<< orphan*/  IXGBE_VTEITR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VTIVAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VTIVAR_MISC ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_get_regs_len (struct net_device*) ; 
 int /*<<< orphan*/ * ixgbevf_reg_names ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixgbevf_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbevf_get_regs(struct net_device *netdev,
			     struct ethtool_regs *regs,
			     void *p)
{
	struct ixgbevf_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;
	u32 *regs_buff = p;
	u32 regs_len = ixgbevf_get_regs_len(netdev);
	u8 i;

	memset(p, 0, regs_len);

	regs->version = (1 << 24) | hw->revision_id << 16 | hw->device_id;

	/* General Registers */
	regs_buff[0] = IXGBE_READ_REG(hw, IXGBE_VFCTRL);
	regs_buff[1] = IXGBE_READ_REG(hw, IXGBE_VFSTATUS);
	regs_buff[2] = IXGBE_READ_REG(hw, IXGBE_VFLINKS);
	regs_buff[3] = IXGBE_READ_REG(hw, IXGBE_VFRXMEMWRAP);
	regs_buff[4] = IXGBE_READ_REG(hw, IXGBE_VFFRTIMER);

	/* Interrupt */
	/* don't read EICR because it can clear interrupt causes, instead
	 * read EICS which is a shadow but doesn't clear EICR */
	regs_buff[5] = IXGBE_READ_REG(hw, IXGBE_VTEICS);
	regs_buff[6] = IXGBE_READ_REG(hw, IXGBE_VTEICS);
	regs_buff[7] = IXGBE_READ_REG(hw, IXGBE_VTEIMS);
	regs_buff[8] = IXGBE_READ_REG(hw, IXGBE_VTEIMC);
	regs_buff[9] = IXGBE_READ_REG(hw, IXGBE_VTEIAC);
	regs_buff[10] = IXGBE_READ_REG(hw, IXGBE_VTEIAM);
	regs_buff[11] = IXGBE_READ_REG(hw, IXGBE_VTEITR(0));
	regs_buff[12] = IXGBE_READ_REG(hw, IXGBE_VTIVAR(0));
	regs_buff[13] = IXGBE_READ_REG(hw, IXGBE_VTIVAR_MISC);

	/* Receive DMA */
	for (i = 0; i < 2; i++)
		regs_buff[14 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDBAL(i));
	for (i = 0; i < 2; i++)
		regs_buff[16 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDBAH(i));
	for (i = 0; i < 2; i++)
		regs_buff[18 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDLEN(i));
	for (i = 0; i < 2; i++)
		regs_buff[20 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDH(i));
	for (i = 0; i < 2; i++)
		regs_buff[22 + i] = IXGBE_READ_REG(hw, IXGBE_VFRDT(i));
	for (i = 0; i < 2; i++)
		regs_buff[24 + i] = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(i));
	for (i = 0; i < 2; i++)
		regs_buff[26 + i] = IXGBE_READ_REG(hw, IXGBE_VFSRRCTL(i));

	/* Receive */
	regs_buff[28] = IXGBE_READ_REG(hw, IXGBE_VFPSRTYPE);

	/* Transmit */
	for (i = 0; i < 2; i++)
		regs_buff[29 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDBAL(i));
	for (i = 0; i < 2; i++)
		regs_buff[31 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDBAH(i));
	for (i = 0; i < 2; i++)
		regs_buff[33 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDLEN(i));
	for (i = 0; i < 2; i++)
		regs_buff[35 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDH(i));
	for (i = 0; i < 2; i++)
		regs_buff[37 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDT(i));
	for (i = 0; i < 2; i++)
		regs_buff[39 + i] = IXGBE_READ_REG(hw, IXGBE_VFTXDCTL(i));
	for (i = 0; i < 2; i++)
		regs_buff[41 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDWBAL(i));
	for (i = 0; i < 2; i++)
		regs_buff[43 + i] = IXGBE_READ_REG(hw, IXGBE_VFTDWBAH(i));

	for (i = 0; i < ARRAY_SIZE(ixgbevf_reg_names); i++)
		hw_dbg(hw, "%s\t%8.8x\n", ixgbevf_reg_names[i], regs_buff[i]);
}