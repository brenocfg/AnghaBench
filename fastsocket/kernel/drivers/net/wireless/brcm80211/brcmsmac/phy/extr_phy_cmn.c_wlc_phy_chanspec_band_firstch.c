#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
typedef  size_t u16 ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {size_t bw; scalar_t__ a_band_high_disable; } ;
struct TYPE_3__ {size_t chan; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 size_t BRCM_BAND_2G ; 
 size_t BRCM_BAND_5G ; 
 scalar_t__ CH_10MHZ_APART ; 
 size_t CH_MAX_2G_CHANNEL ; 
 size_t FIRST_REF5_CHANNUM ; 
 int /*<<< orphan*/  INVCHANSPEC ; 
 scalar_t__ ISNPHY (struct brcms_phy*) ; 
 size_t LAST_REF5_CHANNUM ; 
 size_t WL_CHANSPEC_BAND_2G ; 
 size_t WL_CHANSPEC_BAND_5G ; 
 size_t WL_CHANSPEC_BW_40 ; 
 size_t WL_CHANSPEC_CTL_SB_LOWER ; 
 size_t ch20mhz_chspec (size_t) ; 
 TYPE_1__* chan_info_all ; 
 size_t upper_20_sb (size_t) ; 

u16 wlc_phy_chanspec_band_firstch(struct brcms_phy_pub *ppi, uint band)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	uint i;
	uint channel;
	u16 chspec;

	for (i = 0; i < ARRAY_SIZE(chan_info_all); i++) {
		channel = chan_info_all[i].chan;

		if (ISNPHY(pi) && pi->bw == WL_CHANSPEC_BW_40) {
			uint j;

			for (j = 0; j < ARRAY_SIZE(chan_info_all); j++) {
				if (chan_info_all[j].chan ==
				    channel + CH_10MHZ_APART)
					break;
			}

			if (j == ARRAY_SIZE(chan_info_all))
				continue;

			channel = upper_20_sb(channel);
			chspec =  channel | WL_CHANSPEC_BW_40 |
				  WL_CHANSPEC_CTL_SB_LOWER;
			if (band == BRCM_BAND_2G)
				chspec |= WL_CHANSPEC_BAND_2G;
			else
				chspec |= WL_CHANSPEC_BAND_5G;
		} else
			chspec = ch20mhz_chspec(channel);

		if ((pi->a_band_high_disable) && (channel >= FIRST_REF5_CHANNUM)
		    && (channel <= LAST_REF5_CHANNUM))
			continue;

		if ((band == BRCM_BAND_2G && channel <= CH_MAX_2G_CHANNEL) ||
		    (band == BRCM_BAND_5G && channel > CH_MAX_2G_CHANNEL))
			return chspec;
	}

	return (u16) INVCHANSPEC;
}