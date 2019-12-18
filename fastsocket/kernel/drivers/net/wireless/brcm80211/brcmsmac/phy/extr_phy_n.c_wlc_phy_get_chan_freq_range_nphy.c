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
typedef  scalar_t__ uint ;
typedef  int /*<<< orphan*/  u8 ;
struct chan_info_nphy_radio205x {int dummy; } ;
struct chan_info_nphy_radio2057_rev5 {int dummy; } ;
struct chan_info_nphy_radio2057 {int dummy; } ;
struct chan_info_nphy_2055 {int dummy; } ;
struct brcms_phy {int /*<<< orphan*/  radio_chanspec; } ;

/* Variables and functions */
 int BASE_HIGH_5G_CHAN ; 
 int BASE_LOW_5G_CHAN ; 
 int BASE_MID_5G_CHAN ; 
 scalar_t__ CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WL_CHAN_FREQ_RANGE_2G ; 
 int /*<<< orphan*/  WL_CHAN_FREQ_RANGE_5GH ; 
 int /*<<< orphan*/  WL_CHAN_FREQ_RANGE_5GL ; 
 int /*<<< orphan*/  WL_CHAN_FREQ_RANGE_5GM ; 
 int /*<<< orphan*/  wlc_phy_chan2freq_nphy (struct brcms_phy*,scalar_t__,int*,struct chan_info_nphy_radio2057 const**,struct chan_info_nphy_radio205x const**,struct chan_info_nphy_radio2057_rev5 const**,struct chan_info_nphy_2055 const**) ; 

u8 wlc_phy_get_chan_freq_range_nphy(struct brcms_phy *pi, uint channel)
{
	int freq;
	const struct chan_info_nphy_radio2057 *t0 = NULL;
	const struct chan_info_nphy_radio205x *t1 = NULL;
	const struct chan_info_nphy_radio2057_rev5 *t2 = NULL;
	const struct chan_info_nphy_2055 *t3 = NULL;

	if (channel == 0)
		channel = CHSPEC_CHANNEL(pi->radio_chanspec);

	wlc_phy_chan2freq_nphy(pi, channel, &freq, &t0, &t1, &t2, &t3);

	if (CHSPEC_IS2G(pi->radio_chanspec))
		return WL_CHAN_FREQ_RANGE_2G;

	if ((freq >= BASE_LOW_5G_CHAN) && (freq < BASE_MID_5G_CHAN))
		return WL_CHAN_FREQ_RANGE_5GL;
	else if ((freq >= BASE_MID_5G_CHAN) && (freq < BASE_HIGH_5G_CHAN))
		return WL_CHAN_FREQ_RANGE_5GM;
	else
		return WL_CHAN_FREQ_RANGE_5GH;
}