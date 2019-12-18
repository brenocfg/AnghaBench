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
typedef  int /*<<< orphan*/  u16 ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CT_PDOWN ; 
 int /*<<< orphan*/  PHY_CT_RESET ; 
 int /*<<< orphan*/  PHY_MARV_CTRL ; 
 int /*<<< orphan*/  PHY_MARV_PHY_CTRL ; 
 int /*<<< orphan*/  PHY_M_PC_POL_R_DIS ; 
 int /*<<< orphan*/  gm_phy_read (struct skge_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gm_phy_write (struct skge_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yukon_suspend(struct skge_hw *hw, int port)
{
	u16 ctrl;

	ctrl = gm_phy_read(hw, port, PHY_MARV_PHY_CTRL);
	ctrl |= PHY_M_PC_POL_R_DIS;
	gm_phy_write(hw, port, PHY_MARV_PHY_CTRL, ctrl);

	ctrl = gm_phy_read(hw, port, PHY_MARV_CTRL);
	ctrl |= PHY_CT_RESET;
	gm_phy_write(hw, port, PHY_MARV_CTRL, ctrl);

	/* switch IEEE compatible power down mode on */
	ctrl = gm_phy_read(hw, port, PHY_MARV_CTRL);
	ctrl |= PHY_CT_PDOWN;
	gm_phy_write(hw, port, PHY_MARV_CTRL, ctrl);
}