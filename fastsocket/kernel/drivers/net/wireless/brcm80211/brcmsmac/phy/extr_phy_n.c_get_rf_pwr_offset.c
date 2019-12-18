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
struct TYPE_2__ {int radiorev; } ;
struct brcms_phy {TYPE_1__ pubpi; int /*<<< orphan*/  radio_chanspec; } ;
typedef  size_t s32 ;
typedef  size_t s16 ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__* nphy_papd_padgain_dlt_2g_2057rev3n4 ; 
 scalar_t__* nphy_papd_padgain_dlt_2g_2057rev5 ; 
 scalar_t__* nphy_papd_padgain_dlt_2g_2057rev7 ; 
 scalar_t__* nphy_papd_pgagain_dlt_5g_2057 ; 
 scalar_t__* nphy_papd_pgagain_dlt_5g_2057rev7 ; 

__attribute__((used)) static s32 get_rf_pwr_offset(struct brcms_phy *pi, s16 pga_gn, s16 pad_gn)
{
	s32 rfpwr_offset = 0;

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		if ((pi->pubpi.radiorev == 3) ||
		    (pi->pubpi.radiorev == 4) ||
		    (pi->pubpi.radiorev == 6))
			rfpwr_offset = (s16)
				       nphy_papd_padgain_dlt_2g_2057rev3n4
				       [pad_gn];
		else if (pi->pubpi.radiorev == 5)
			rfpwr_offset = (s16)
				       nphy_papd_padgain_dlt_2g_2057rev5
				       [pad_gn];
		else if ((pi->pubpi.radiorev == 7)
			 || (pi->pubpi.radiorev ==
			     8))
			rfpwr_offset = (s16)
				       nphy_papd_padgain_dlt_2g_2057rev7
				       [pad_gn];
	} else {
		if ((pi->pubpi.radiorev == 3) ||
		    (pi->pubpi.radiorev == 4) ||
		    (pi->pubpi.radiorev == 6))
			rfpwr_offset = (s16)
				       nphy_papd_pgagain_dlt_5g_2057
				       [pga_gn];
		else if ((pi->pubpi.radiorev == 7)
			 || (pi->pubpi.radiorev ==
			     8))
			rfpwr_offset = (s16)
				       nphy_papd_pgagain_dlt_5g_2057rev7
				       [pga_gn];
	}
	return rfpwr_offset;
}