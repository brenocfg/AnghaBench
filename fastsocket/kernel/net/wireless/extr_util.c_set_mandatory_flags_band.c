#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* rx_mask; } ;
struct TYPE_6__ {TYPE_2__ mcs; int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_supported_band {int n_bitrates; TYPE_3__ ht_cap; TYPE_1__* bitrates; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
struct TYPE_4__ {int bitrate; int flags; } ;

/* Variables and functions */
#define  IEEE80211_BAND_2GHZ 131 
#define  IEEE80211_BAND_5GHZ 130 
#define  IEEE80211_BAND_60GHZ 129 
#define  IEEE80211_NUM_BANDS 128 
 int IEEE80211_RATE_ERP_G ; 
 int IEEE80211_RATE_MANDATORY_A ; 
 int IEEE80211_RATE_MANDATORY_B ; 
 int IEEE80211_RATE_MANDATORY_G ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void set_mandatory_flags_band(struct ieee80211_supported_band *sband,
				     enum ieee80211_band band)
{
	int i, want;

	switch (band) {
	case IEEE80211_BAND_5GHZ:
		want = 3;
		for (i = 0; i < sband->n_bitrates; i++) {
			if (sband->bitrates[i].bitrate == 60 ||
			    sband->bitrates[i].bitrate == 120 ||
			    sband->bitrates[i].bitrate == 240) {
				sband->bitrates[i].flags |=
					IEEE80211_RATE_MANDATORY_A;
				want--;
			}
		}
		WARN_ON(want);
		break;
	case IEEE80211_BAND_2GHZ:
		want = 7;
		for (i = 0; i < sband->n_bitrates; i++) {
			if (sband->bitrates[i].bitrate == 10) {
				sband->bitrates[i].flags |=
					IEEE80211_RATE_MANDATORY_B |
					IEEE80211_RATE_MANDATORY_G;
				want--;
			}

			if (sband->bitrates[i].bitrate == 20 ||
			    sband->bitrates[i].bitrate == 55 ||
			    sband->bitrates[i].bitrate == 110 ||
			    sband->bitrates[i].bitrate == 60 ||
			    sband->bitrates[i].bitrate == 120 ||
			    sband->bitrates[i].bitrate == 240) {
				sband->bitrates[i].flags |=
					IEEE80211_RATE_MANDATORY_G;
				want--;
			}

			if (sband->bitrates[i].bitrate != 10 &&
			    sband->bitrates[i].bitrate != 20 &&
			    sband->bitrates[i].bitrate != 55 &&
			    sband->bitrates[i].bitrate != 110)
				sband->bitrates[i].flags |=
					IEEE80211_RATE_ERP_G;
		}
		WARN_ON(want != 0 && want != 3 && want != 6);
		break;
	case IEEE80211_BAND_60GHZ:
		/* check for mandatory HT MCS 1..4 */
		WARN_ON(!sband->ht_cap.ht_supported);
		WARN_ON((sband->ht_cap.mcs.rx_mask[0] & 0x1e) != 0x1e);
		break;
	case IEEE80211_NUM_BANDS:
		WARN_ON(1);
		break;
	}
}