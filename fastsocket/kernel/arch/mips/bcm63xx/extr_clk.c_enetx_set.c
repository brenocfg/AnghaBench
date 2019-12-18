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
typedef  int /*<<< orphan*/  u32 ;
struct clk {scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ BCMCPU_IS_6358 () ; 
 int /*<<< orphan*/  CKCTL_6358_ENET0_EN ; 
 int /*<<< orphan*/  CKCTL_6358_ENET1_EN ; 
 int /*<<< orphan*/  bcm_hwclock_set (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_disable_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enable_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_enet_misc ; 

__attribute__((used)) static void enetx_set(struct clk *clk, int enable)
{
	if (enable)
		clk_enable_unlocked(&clk_enet_misc);
	else
		clk_disable_unlocked(&clk_enet_misc);

	if (BCMCPU_IS_6358()) {
		u32 mask;

		if (clk->id == 0)
			mask = CKCTL_6358_ENET0_EN;
		else
			mask = CKCTL_6358_ENET1_EN;
		bcm_hwclock_set(mask, enable);
	}
}