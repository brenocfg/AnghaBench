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
typedef  int u16 ;
struct brcms_phy {TYPE_1__* sh; int /*<<< orphan*/  d11core; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  physhim; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int LCN_VBAT_SCALE_DEN ; 
 int LCN_VBAT_SCALE_NOM ; 
 int MCTL_EN_MAC ; 
 int /*<<< orphan*/  VBATSENSE ; 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maccontrol ; 
 int read_phy_reg (struct brcms_phy*,int) ; 
 int /*<<< orphan*/  wlapi_enable_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlapi_suspend_mac_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_vbat_temp_sense_setup (struct brcms_phy*,int /*<<< orphan*/ ) ; 

s8 wlc_lcnphy_vbatsense(struct brcms_phy *pi, bool mode)
{
	u16 vbatsenseval;
	s32 avg = 0;
	bool suspend = false;

	if (mode == 1) {
		suspend = (0 == (bcma_read32(pi->d11core,
					     D11REGOFFS(maccontrol)) &
				 MCTL_EN_MAC));
		if (!suspend)
			wlapi_suspend_mac_and_wait(pi->sh->physhim);
		wlc_lcnphy_vbat_temp_sense_setup(pi, VBATSENSE);
	}

	vbatsenseval = read_phy_reg(pi, 0x475) & 0x1FF;

	if (vbatsenseval > 255)
		avg = (s32) (vbatsenseval - 512);
	else
		avg = (s32) vbatsenseval;

	avg =	(avg * LCN_VBAT_SCALE_NOM +
		 (LCN_VBAT_SCALE_DEN >> 1)) / LCN_VBAT_SCALE_DEN;

	if (mode == 1) {
		if (!suspend)
			wlapi_enable_mac(pi->sh->physhim);
	}
	return (s8) avg;
}