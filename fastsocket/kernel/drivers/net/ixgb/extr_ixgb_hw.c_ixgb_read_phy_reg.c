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
typedef  int /*<<< orphan*/  u16 ;
struct ixgb_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int IXGB_MAX_PHY_ADDRESS ; 
 int IXGB_MAX_PHY_DEV_TYPE ; 
 int IXGB_MAX_PHY_REG_ADDRESS ; 
 int IXGB_MSCA_ADDR_CYCLE ; 
 int IXGB_MSCA_DEV_TYPE_SHIFT ; 
 int IXGB_MSCA_MDI_COMMAND ; 
 int IXGB_MSCA_NP_ADDR_SHIFT ; 
 int IXGB_MSCA_PHY_ADDR_SHIFT ; 
 int IXGB_MSCA_READ ; 
 int IXGB_MSRWD_READ_DATA_SHIFT ; 
 int IXGB_READ_REG (struct ixgb_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (struct ixgb_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MSCA ; 
 int /*<<< orphan*/  MSRWD ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u16
ixgb_read_phy_reg(struct ixgb_hw *hw,
		u32 reg_address,
		u32 phy_address,
		u32 device_type)
{
	u32 i;
	u32 data;
	u32 command = 0;

	ASSERT(reg_address <= IXGB_MAX_PHY_REG_ADDRESS);
	ASSERT(phy_address <= IXGB_MAX_PHY_ADDRESS);
	ASSERT(device_type <= IXGB_MAX_PHY_DEV_TYPE);

	/* Setup and write the address cycle command */
	command = ((reg_address << IXGB_MSCA_NP_ADDR_SHIFT) |
		   (device_type << IXGB_MSCA_DEV_TYPE_SHIFT) |
		   (phy_address << IXGB_MSCA_PHY_ADDR_SHIFT) |
		   (IXGB_MSCA_ADDR_CYCLE | IXGB_MSCA_MDI_COMMAND));

	IXGB_WRITE_REG(hw, MSCA, command);

    /**************************************************************
    ** Check every 10 usec to see if the address cycle completed
    ** The COMMAND bit will clear when the operation is complete.
    ** This may take as long as 64 usecs (we'll wait 100 usecs max)
    ** from the CPU Write to the Ready bit assertion.
    **************************************************************/

	for (i = 0; i < 10; i++)
	{
		udelay(10);

		command = IXGB_READ_REG(hw, MSCA);

		if ((command & IXGB_MSCA_MDI_COMMAND) == 0)
			break;
	}

	ASSERT((command & IXGB_MSCA_MDI_COMMAND) == 0);

	/* Address cycle complete, setup and write the read command */
	command = ((reg_address << IXGB_MSCA_NP_ADDR_SHIFT) |
		   (device_type << IXGB_MSCA_DEV_TYPE_SHIFT) |
		   (phy_address << IXGB_MSCA_PHY_ADDR_SHIFT) |
		   (IXGB_MSCA_READ | IXGB_MSCA_MDI_COMMAND));

	IXGB_WRITE_REG(hw, MSCA, command);

    /**************************************************************
    ** Check every 10 usec to see if the read command completed
    ** The COMMAND bit will clear when the operation is complete.
    ** The read may take as long as 64 usecs (we'll wait 100 usecs max)
    ** from the CPU Write to the Ready bit assertion.
    **************************************************************/

	for (i = 0; i < 10; i++)
	{
		udelay(10);

		command = IXGB_READ_REG(hw, MSCA);

		if ((command & IXGB_MSCA_MDI_COMMAND) == 0)
			break;
	}

	ASSERT((command & IXGB_MSCA_MDI_COMMAND) == 0);

	/* Operation is complete, get the data from the MDIO Read/Write Data
	 * register and return.
	 */
	data = IXGB_READ_REG(hw, MSRWD);
	data >>= IXGB_MSRWD_READ_DATA_SHIFT;
	return((u16) data);
}