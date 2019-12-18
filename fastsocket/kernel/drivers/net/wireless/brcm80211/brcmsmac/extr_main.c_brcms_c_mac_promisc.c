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
typedef  int uint ;
typedef  int u32 ;
struct brcms_c_info {int filter_flags; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int FIF_BCN_PRBRESP_PROMISC ; 
 int FIF_CONTROL ; 
 int FIF_FCSFAIL ; 
 int FIF_OTHER_BSS ; 
 int FIF_PROMISC_IN_BSS ; 
 int FIF_PSPOLL ; 
 int MCTL_BCNS_PROMISC ; 
 int MCTL_KEEPBADFCS ; 
 int MCTL_KEEPCONTROL ; 
 int MCTL_PROMISC ; 
 int /*<<< orphan*/  brcms_b_mctrl (int /*<<< orphan*/ ,int,int) ; 

void brcms_c_mac_promisc(struct brcms_c_info *wlc, uint filter_flags)
{
	u32 promisc_bits = 0;

	wlc->filter_flags = filter_flags;

	if (filter_flags & (FIF_PROMISC_IN_BSS | FIF_OTHER_BSS))
		promisc_bits |= MCTL_PROMISC;

	if (filter_flags & FIF_BCN_PRBRESP_PROMISC)
		promisc_bits |= MCTL_BCNS_PROMISC;

	if (filter_flags & FIF_FCSFAIL)
		promisc_bits |= MCTL_KEEPBADFCS;

	if (filter_flags & (FIF_CONTROL | FIF_PSPOLL))
		promisc_bits |= MCTL_KEEPCONTROL;

	brcms_b_mctrl(wlc->hw,
		MCTL_PROMISC | MCTL_BCNS_PROMISC |
		MCTL_KEEPCONTROL | MCTL_KEEPBADFCS,
		promisc_bits);
}