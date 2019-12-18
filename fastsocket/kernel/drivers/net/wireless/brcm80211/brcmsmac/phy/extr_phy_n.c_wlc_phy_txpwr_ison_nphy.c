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
 int read_phy_reg (struct brcms_phy*,int) ; 

__attribute__((used)) static bool wlc_phy_txpwr_ison_nphy(struct brcms_phy *pi)
{
	return read_phy_reg((pi), 0x1e7) & ((0x1 << 15) |
					    (0x1 << 14) | (0x1 << 13));
}