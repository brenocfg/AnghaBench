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
struct brcms_c_rateset {int dummy; } ;
struct brcms_c_info {TYPE_1__* band; } ;
struct TYPE_2__ {scalar_t__ bandtype; scalar_t__ gmode; } ;

/* Variables and functions */
 scalar_t__ BRCMS_PHY_11N_CAP (TYPE_1__*) ; 
 scalar_t__ BRCM_BAND_5G ; 
 struct brcms_c_rateset cck_ofdm_mimo_rates ; 
 struct brcms_c_rateset cck_ofdm_rates ; 
 struct brcms_c_rateset cck_rates ; 
 struct brcms_c_rateset ofdm_mimo_rates ; 

__attribute__((used)) static const struct brcms_c_rateset *
brcms_c_rateset_get_hwrs(struct brcms_c_info *wlc)
{
	const struct brcms_c_rateset *rs_dflt;

	if (BRCMS_PHY_11N_CAP(wlc->band)) {
		if (wlc->band->bandtype == BRCM_BAND_5G)
			rs_dflt = &ofdm_mimo_rates;
		else
			rs_dflt = &cck_ofdm_mimo_rates;
	} else if (wlc->band->gmode)
		rs_dflt = &cck_ofdm_rates;
	else
		rs_dflt = &cck_rates;

	return rs_dflt;
}