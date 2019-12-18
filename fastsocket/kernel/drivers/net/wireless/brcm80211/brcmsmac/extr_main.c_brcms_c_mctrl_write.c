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
struct brcms_hardware {int /*<<< orphan*/  d11core; scalar_t__ mute_override; scalar_t__ wake_override; int /*<<< orphan*/  maccontrol; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCTL_AP ; 
 int /*<<< orphan*/  MCTL_INFRA ; 
 int /*<<< orphan*/  MCTL_WAKE ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcms_c_mctrl_write(struct brcms_hardware *wlc_hw)
{
	u32 maccontrol = wlc_hw->maccontrol;

	/* OR in the wake bit if overridden */
	if (wlc_hw->wake_override)
		maccontrol |= MCTL_WAKE;

	/* set AP and INFRA bits for mute if needed */
	if (wlc_hw->mute_override) {
		maccontrol &= ~(MCTL_AP);
		maccontrol |= MCTL_INFRA;
	}

	bcma_write32(wlc_hw->d11core, D11REGOFFS(maccontrol),
		     maccontrol);
}