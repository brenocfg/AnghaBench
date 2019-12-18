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
typedef  scalar_t__ u32 ;
struct brcms_phy_pub {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_phy_reg (struct brcms_phy*,int) ; 

bool wlc_phy_bist_check_phy(struct brcms_phy_pub *pih)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;
	u32 phybist0, phybist1, phybist2, phybist3, phybist4;

	if (NREV_GE(pi->pubpi.phy_rev, 16))
		return true;

	phybist0 = read_phy_reg(pi, 0x0e);
	phybist1 = read_phy_reg(pi, 0x0f);
	phybist2 = read_phy_reg(pi, 0xea);
	phybist3 = read_phy_reg(pi, 0xeb);
	phybist4 = read_phy_reg(pi, 0x156);

	if ((phybist0 == 0) && (phybist1 == 0x4000) && (phybist2 == 0x1fe0) &&
	    (phybist3 == 0) && (phybist4 == 0))
		return true;

	return false;
}