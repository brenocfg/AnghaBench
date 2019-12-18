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
struct brcms_phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mod_phy_reg (struct brcms_phy*,int,int,int) ; 
 int /*<<< orphan*/  or_phy_reg (struct brcms_phy*,int,int) ; 

__attribute__((used)) static void wlc_lcnphy_set_trsw_override(struct brcms_phy *pi, bool tx, bool rx)
{

	mod_phy_reg(pi, 0x44d,
		    (0x1 << 1) |
		    (0x1 << 0), (tx ? (0x1 << 1) : 0) | (rx ? (0x1 << 0) : 0));

	or_phy_reg(pi, 0x44c, (0x1 << 1) | (0x1 << 0));
}