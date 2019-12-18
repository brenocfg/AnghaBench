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
typedef  int /*<<< orphan*/  u8 ;
struct ti_ohci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_phy_reg (struct ti_ohci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_phy_reg (struct ti_ohci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_phy_reg_mask(struct ti_ohci *ohci, u8 addr, u8 data)
{
	u8 old;

	old = get_phy_reg (ohci, addr);
	old |= data;
	set_phy_reg (ohci, addr, old);

	return;
}