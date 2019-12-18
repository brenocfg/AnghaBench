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
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {int bw; } ;

/* Variables and functions */
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 int /*<<< orphan*/  SICF_BW10 ; 
 int /*<<< orphan*/  SICF_BW20 ; 
 int /*<<< orphan*/  SICF_BW40 ; 
#define  WL_CHANSPEC_BW_10 130 
#define  WL_CHANSPEC_BW_20 129 
#define  WL_CHANSPEC_BW_40 128 

u32 wlc_phy_clk_bwbits(struct brcms_phy_pub *pih)
{
	struct brcms_phy *pi = (struct brcms_phy *) pih;

	u32 phy_bw_clkbits = 0;

	if (pi && (ISNPHY(pi) || ISLCNPHY(pi))) {
		switch (pi->bw) {
		case WL_CHANSPEC_BW_10:
			phy_bw_clkbits = SICF_BW10;
			break;
		case WL_CHANSPEC_BW_20:
			phy_bw_clkbits = SICF_BW20;
			break;
		case WL_CHANSPEC_BW_40:
			phy_bw_clkbits = SICF_BW40;
			break;
		default:
			break;
		}
	}

	return phy_bw_clkbits;
}