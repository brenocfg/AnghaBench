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
typedef  int u32 ;
struct brcms_c_info {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  d11core; int /*<<< orphan*/  sih; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int MCTL_IHR_EN ; 
 int MCTL_PSM_JMP_0 ; 
 int ai_deviceremoved (int /*<<< orphan*/ ) ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 

__attribute__((used)) static bool brcms_deviceremoved(struct brcms_c_info *wlc)
{
	u32 macctrl;

	if (!wlc->hw->clk)
		return ai_deviceremoved(wlc->hw->sih);
	macctrl = bcma_read32(wlc->hw->d11core,
			      D11REGOFFS(maccontrol));
	return (macctrl & (MCTL_PSM_JMP_0 | MCTL_IHR_EN)) != MCTL_IHR_EN;
}