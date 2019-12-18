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
struct TYPE_2__ {int conf; int /*<<< orphan*/  (* write_reg ) (struct inf_hw*,int /*<<< orphan*/ ,int) ;} ;
struct inf_hw {TYPE_1__ ipac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPAC_CONF ; 
 int /*<<< orphan*/  IPAC_MASK ; 
 int /*<<< orphan*/  IPAC_POTA2 ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  stub1 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct inf_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ipac_chip_reset(struct inf_hw *hw)
{
	hw->ipac.write_reg(hw, IPAC_POTA2, 0x20);
	mdelay(5);
	hw->ipac.write_reg(hw, IPAC_POTA2, 0x00);
	mdelay(5);
	hw->ipac.write_reg(hw, IPAC_CONF, hw->ipac.conf);
	hw->ipac.write_reg(hw, IPAC_MASK, 0xc0);
}