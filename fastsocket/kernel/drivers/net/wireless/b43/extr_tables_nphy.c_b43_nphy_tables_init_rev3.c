#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_7__ {size_t antswlut; } ;
struct TYPE_6__ {size_t antswlut; } ;
struct TYPE_8__ {TYPE_3__ ghz2; TYPE_2__ ghz5; } ;
struct ssb_sprom {TYPE_4__ fem; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_1__* dev; } ;
struct TYPE_5__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B43_NTAB_ANT_SW_CTL_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C0_ADJPLT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C0_ESTPLT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C0_GAINCTL_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C0_IQLT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C0_LOFEEDTH_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C1_ADJPLT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C1_ESTPLT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C1_GAINCTL_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C1_IQLT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_C1_LOFEEDTH_R3 ; 
 int /*<<< orphan*/  B43_NTAB_CHANEST_R3 ; 
 int /*<<< orphan*/  B43_NTAB_FRAMELT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_FRAMESTRUCT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_INTLEVEL_R3 ; 
 int /*<<< orphan*/  B43_NTAB_MCS_R3 ; 
 int /*<<< orphan*/  B43_NTAB_NOISEVAR0_R3 ; 
 int /*<<< orphan*/  B43_NTAB_NOISEVAR1_R3 ; 
 int /*<<< orphan*/  B43_NTAB_PILOTLT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_PILOT_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDI20A0_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDI20A1_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDI40A0_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDI40A1_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TDTRN_R3 ; 
 int /*<<< orphan*/  B43_NTAB_TMAP_R3 ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_ntab_adjustpower0_r3 ; 
 int /*<<< orphan*/  b43_ntab_adjustpower1_r3 ; 
 int /*<<< orphan*/ * b43_ntab_antswctl_r3 ; 
 int /*<<< orphan*/  b43_ntab_channelest_r3 ; 
 int /*<<< orphan*/  b43_ntab_estimatepowerlt0_r3 ; 
 int /*<<< orphan*/  b43_ntab_estimatepowerlt1_r3 ; 
 int /*<<< orphan*/  b43_ntab_framelookup_r3 ; 
 int /*<<< orphan*/  b43_ntab_framestruct_r3 ; 
 int /*<<< orphan*/  b43_ntab_gainctl0_r3 ; 
 int /*<<< orphan*/  b43_ntab_gainctl1_r3 ; 
 int /*<<< orphan*/  b43_ntab_intlevel_r3 ; 
 int /*<<< orphan*/  b43_ntab_iqlt0_r3 ; 
 int /*<<< orphan*/  b43_ntab_iqlt1_r3 ; 
 int /*<<< orphan*/  b43_ntab_loftlt0_r3 ; 
 int /*<<< orphan*/  b43_ntab_loftlt1_r3 ; 
 int /*<<< orphan*/  b43_ntab_mcs_r3 ; 
 int /*<<< orphan*/  b43_ntab_noisevar0_r3 ; 
 int /*<<< orphan*/  b43_ntab_noisevar1_r3 ; 
 int /*<<< orphan*/  b43_ntab_pilot_r3 ; 
 int /*<<< orphan*/  b43_ntab_pilotlt_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdi20a0_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdi20a1_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdi40a0_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdi40a1_r3 ; 
 int /*<<< orphan*/  b43_ntab_tdtrn_r3 ; 
 int /*<<< orphan*/  b43_ntab_tmap_r3 ; 
 int /*<<< orphan*/  ntab_upload (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_nphy_tables_init_rev3(struct b43_wldev *dev)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	u8 antswlut;

	if (b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ)
		antswlut = sprom->fem.ghz5.antswlut;
	else
		antswlut = sprom->fem.ghz2.antswlut;

	/* Static tables */
	ntab_upload(dev, B43_NTAB_FRAMESTRUCT_R3, b43_ntab_framestruct_r3);
	ntab_upload(dev, B43_NTAB_PILOT_R3, b43_ntab_pilot_r3);
	ntab_upload(dev, B43_NTAB_TMAP_R3, b43_ntab_tmap_r3);
	ntab_upload(dev, B43_NTAB_INTLEVEL_R3, b43_ntab_intlevel_r3);
	ntab_upload(dev, B43_NTAB_TDTRN_R3, b43_ntab_tdtrn_r3);
	ntab_upload(dev, B43_NTAB_NOISEVAR0_R3, b43_ntab_noisevar0_r3);
	ntab_upload(dev, B43_NTAB_NOISEVAR1_R3, b43_ntab_noisevar1_r3);
	ntab_upload(dev, B43_NTAB_MCS_R3, b43_ntab_mcs_r3);
	ntab_upload(dev, B43_NTAB_TDI20A0_R3, b43_ntab_tdi20a0_r3);
	ntab_upload(dev, B43_NTAB_TDI20A1_R3, b43_ntab_tdi20a1_r3);
	ntab_upload(dev, B43_NTAB_TDI40A0_R3, b43_ntab_tdi40a0_r3);
	ntab_upload(dev, B43_NTAB_TDI40A1_R3, b43_ntab_tdi40a1_r3);
	ntab_upload(dev, B43_NTAB_PILOTLT_R3, b43_ntab_pilotlt_r3);
	ntab_upload(dev, B43_NTAB_CHANEST_R3, b43_ntab_channelest_r3);
	ntab_upload(dev, B43_NTAB_FRAMELT_R3, b43_ntab_framelookup_r3);
	ntab_upload(dev, B43_NTAB_C0_ESTPLT_R3, b43_ntab_estimatepowerlt0_r3);
	ntab_upload(dev, B43_NTAB_C1_ESTPLT_R3, b43_ntab_estimatepowerlt1_r3);
	ntab_upload(dev, B43_NTAB_C0_ADJPLT_R3, b43_ntab_adjustpower0_r3);
	ntab_upload(dev, B43_NTAB_C1_ADJPLT_R3, b43_ntab_adjustpower1_r3);
	ntab_upload(dev, B43_NTAB_C0_GAINCTL_R3, b43_ntab_gainctl0_r3);
	ntab_upload(dev, B43_NTAB_C1_GAINCTL_R3, b43_ntab_gainctl1_r3);
	ntab_upload(dev, B43_NTAB_C0_IQLT_R3, b43_ntab_iqlt0_r3);
	ntab_upload(dev, B43_NTAB_C1_IQLT_R3, b43_ntab_iqlt1_r3);
	ntab_upload(dev, B43_NTAB_C0_LOFEEDTH_R3, b43_ntab_loftlt0_r3);
	ntab_upload(dev, B43_NTAB_C1_LOFEEDTH_R3, b43_ntab_loftlt1_r3);

	/* Volatile tables */
	if (antswlut < ARRAY_SIZE(b43_ntab_antswctl_r3))
		ntab_upload(dev, B43_NTAB_ANT_SW_CTL_R3,
			    b43_ntab_antswctl_r3[antswlut]);
	else
		B43_WARN_ON(1);
}