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
struct brcms_phy {scalar_t__ phy_wreg; int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_set16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_wflush16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phyregaddr ; 
 int /*<<< orphan*/  phyregdata ; 

void or_phy_reg(struct brcms_phy *pi, u16 addr, u16 val)
{
	bcma_wflush16(pi->d11core, D11REGOFFS(phyregaddr), addr);
	bcma_set16(pi->d11core, D11REGOFFS(phyregdata), val);
	pi->phy_wreg = 0;
}