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
typedef  size_t uint ;
typedef  size_t u32 ;
struct chan_info_nphy_radio205x {size_t chan; int freq; } ;
struct chan_info_nphy_radio2057_rev5 {size_t chan; int freq; } ;
struct chan_info_nphy_radio2057 {size_t chan; int freq; } ;
struct chan_info_nphy_2055 {size_t chan; int freq; } ;
struct TYPE_2__ {int radiorev; int radiover; int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {TYPE_1__ pubpi; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct chan_info_nphy_radio205x*) ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ NREV_IS (int /*<<< orphan*/ ,int) ; 
 int WL_CHAN_FREQ_RANGE_2G ; 
 struct chan_info_nphy_radio205x* chan_info_nphy_2055 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev3_2056 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev4_2056_A1 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev5_2056v5 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev5n6_2056v7 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev6_2056v11 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev6_2056v6 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev6_2056v8 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev7_2057_rev4 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev8_2057_rev5 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev8_2057_rev7 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev8_2057_rev8 ; 
 struct chan_info_nphy_radio205x* chan_info_nphyrev9_2057_rev5v1 ; 

__attribute__((used)) static bool
wlc_phy_chan2freq_nphy(struct brcms_phy *pi, uint channel, int *f,
		       const struct chan_info_nphy_radio2057 **t0,
		       const struct chan_info_nphy_radio205x **t1,
		       const struct chan_info_nphy_radio2057_rev5 **t2,
		       const struct chan_info_nphy_2055 **t3)
{
	uint i;
	const struct chan_info_nphy_radio2057 *chan_info_tbl_p_0 = NULL;
	const struct chan_info_nphy_radio205x *chan_info_tbl_p_1 = NULL;
	const struct chan_info_nphy_radio2057_rev5 *chan_info_tbl_p_2 = NULL;
	u32 tbl_len = 0;

	int freq = 0;

	if (NREV_GE(pi->pubpi.phy_rev, 7)) {

		if (NREV_IS(pi->pubpi.phy_rev, 7)) {

			chan_info_tbl_p_0 = chan_info_nphyrev7_2057_rev4;
			tbl_len = ARRAY_SIZE(chan_info_nphyrev7_2057_rev4);

		} else if (NREV_IS(pi->pubpi.phy_rev, 8)
			   || NREV_IS(pi->pubpi.phy_rev, 9)) {
			switch (pi->pubpi.radiorev) {

			case 5:

				if (pi->pubpi.radiover == 0x0) {

					chan_info_tbl_p_2 =
						chan_info_nphyrev8_2057_rev5;
					tbl_len = ARRAY_SIZE(
						  chan_info_nphyrev8_2057_rev5);

				} else if (pi->pubpi.radiover == 0x1) {

					chan_info_tbl_p_2 =
						chan_info_nphyrev9_2057_rev5v1;
					tbl_len = ARRAY_SIZE(
						chan_info_nphyrev9_2057_rev5v1);

				}
				break;

			case 7:
				chan_info_tbl_p_0 =
					chan_info_nphyrev8_2057_rev7;
				tbl_len = ARRAY_SIZE(
						  chan_info_nphyrev8_2057_rev7);
				break;

			case 8:
				chan_info_tbl_p_0 =
					chan_info_nphyrev8_2057_rev8;
				tbl_len = ARRAY_SIZE(
						  chan_info_nphyrev8_2057_rev8);
				break;

			default:
				break;
			}
		} else if (NREV_IS(pi->pubpi.phy_rev, 16)) {

			chan_info_tbl_p_0 = chan_info_nphyrev8_2057_rev8;
			tbl_len = ARRAY_SIZE(chan_info_nphyrev8_2057_rev8);
		} else {
			goto fail;
		}

		for (i = 0; i < tbl_len; i++) {
			if (pi->pubpi.radiorev == 5) {

				if (chan_info_tbl_p_2[i].chan == channel)
					break;
			} else {

				if (chan_info_tbl_p_0[i].chan == channel)
					break;
			}
		}

		if (i >= tbl_len)
			goto fail;

		if (pi->pubpi.radiorev == 5) {
			*t2 = &chan_info_tbl_p_2[i];
			freq = chan_info_tbl_p_2[i].freq;
		} else {
			*t0 = &chan_info_tbl_p_0[i];
			freq = chan_info_tbl_p_0[i].freq;
		}

	} else if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		if (NREV_IS(pi->pubpi.phy_rev, 3)) {
			chan_info_tbl_p_1 = chan_info_nphyrev3_2056;
			tbl_len = ARRAY_SIZE(chan_info_nphyrev3_2056);
		} else if (NREV_IS(pi->pubpi.phy_rev, 4)) {
			chan_info_tbl_p_1 = chan_info_nphyrev4_2056_A1;
			tbl_len = ARRAY_SIZE(chan_info_nphyrev4_2056_A1);
		} else if (NREV_IS(pi->pubpi.phy_rev, 5)
			   || NREV_IS(pi->pubpi.phy_rev, 6)) {
			switch (pi->pubpi.radiorev) {
			case 5:
				chan_info_tbl_p_1 = chan_info_nphyrev5_2056v5;
				tbl_len = ARRAY_SIZE(chan_info_nphyrev5_2056v5);
				break;
			case 6:
				chan_info_tbl_p_1 = chan_info_nphyrev6_2056v6;
				tbl_len = ARRAY_SIZE(chan_info_nphyrev6_2056v6);
				break;
			case 7:
			case 9:
				chan_info_tbl_p_1 = chan_info_nphyrev5n6_2056v7;
				tbl_len =
					ARRAY_SIZE(chan_info_nphyrev5n6_2056v7);
				break;
			case 8:
				chan_info_tbl_p_1 = chan_info_nphyrev6_2056v8;
				tbl_len = ARRAY_SIZE(chan_info_nphyrev6_2056v8);
				break;
			case 11:
				chan_info_tbl_p_1 = chan_info_nphyrev6_2056v11;
				tbl_len = ARRAY_SIZE(
						    chan_info_nphyrev6_2056v11);
				break;
			default:
				break;
			}
		}

		for (i = 0; i < tbl_len; i++) {
			if (chan_info_tbl_p_1[i].chan == channel)
				break;
		}

		if (i >= tbl_len)
			goto fail;

		*t1 = &chan_info_tbl_p_1[i];
		freq = chan_info_tbl_p_1[i].freq;

	} else {
		for (i = 0; i < ARRAY_SIZE(chan_info_nphy_2055); i++)
			if (chan_info_nphy_2055[i].chan == channel)
				break;

		if (i >= ARRAY_SIZE(chan_info_nphy_2055))
			goto fail;

		*t3 = &chan_info_nphy_2055[i];
		freq = chan_info_nphy_2055[i].freq;
	}

	*f = freq;
	return true;

fail:
	*f = WL_CHAN_FREQ_RANGE_2G;
	return false;
}