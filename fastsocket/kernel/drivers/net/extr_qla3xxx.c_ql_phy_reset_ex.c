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
struct ql3_adapter {size_t mac_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_REG ; 
 int /*<<< orphan*/ * PHYAddr ; 
 int /*<<< orphan*/  PHY_CTRL_SOFT_RESET ; 
 int /*<<< orphan*/  ql_mii_write_reg_ex (struct ql3_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_phy_reset_ex(struct ql3_adapter *qdev)
{
	ql_mii_write_reg_ex(qdev, CONTROL_REG, PHY_CTRL_SOFT_RESET,
			    PHYAddr[qdev->mac_index]);
}