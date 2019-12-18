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
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy {scalar_t__ a_band_high_disable; } ;
struct brcms_chanvec {int /*<<< orphan*/  vec; } ;
struct TYPE_3__ {size_t chan; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 size_t BRCM_BAND_2G ; 
 size_t BRCM_BAND_5G ; 
 size_t CH_MAX_2G_CHANNEL ; 
 size_t FIRST_REF5_CHANNUM ; 
 size_t LAST_REF5_CHANNUM ; 
 TYPE_1__* chan_info_all ; 
 int /*<<< orphan*/  memset (struct brcms_chanvec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,size_t) ; 

void
wlc_phy_chanspec_band_validch(struct brcms_phy_pub *ppi, uint band,
			      struct brcms_chanvec *channels)
{
	struct brcms_phy *pi = (struct brcms_phy *) ppi;
	uint i;
	uint channel;

	memset(channels, 0, sizeof(struct brcms_chanvec));

	for (i = 0; i < ARRAY_SIZE(chan_info_all); i++) {
		channel = chan_info_all[i].chan;

		if ((pi->a_band_high_disable) && (channel >= FIRST_REF5_CHANNUM)
		    && (channel <= LAST_REF5_CHANNUM))
			continue;

		if ((band == BRCM_BAND_2G && channel <= CH_MAX_2G_CHANNEL) ||
		    (band == BRCM_BAND_5G && channel > CH_MAX_2G_CHANNEL))
			setbit(channels->vec, channel);
	}
}