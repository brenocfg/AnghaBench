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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NTAB_BDI ; 
 int /*<<< orphan*/  B43_NTAB_C0_ADJPLT ; 
 int /*<<< orphan*/  B43_NTAB_C0_ESTPLT ; 
 int /*<<< orphan*/  B43_NTAB_C0_GAINCTL ; 
 int /*<<< orphan*/  B43_NTAB_C0_IQLT ; 
 int /*<<< orphan*/  B43_NTAB_C0_LOFEEDTH ; 
 int /*<<< orphan*/  B43_NTAB_C1_ADJPLT ; 
 int /*<<< orphan*/  B43_NTAB_C1_ESTPLT ; 
 int /*<<< orphan*/  B43_NTAB_C1_GAINCTL ; 
 int /*<<< orphan*/  B43_NTAB_C1_IQLT ; 
 int /*<<< orphan*/  B43_NTAB_C1_LOFEEDTH ; 
 int /*<<< orphan*/  B43_NTAB_CHANEST ; 
 int /*<<< orphan*/  B43_NTAB_FRAMELT ; 
 int /*<<< orphan*/  B43_NTAB_FRAMESTRUCT ; 
 int /*<<< orphan*/  B43_NTAB_INTLEVEL ; 
 int /*<<< orphan*/  B43_NTAB_MCS ; 
 int /*<<< orphan*/  B43_NTAB_NOISEVAR10 ; 
 int /*<<< orphan*/  B43_NTAB_NOISEVAR11 ; 
 int /*<<< orphan*/  B43_NTAB_PILOT ; 
 int /*<<< orphan*/  B43_NTAB_PILOTLT ; 
 int /*<<< orphan*/  B43_NTAB_TDI20A0 ; 
 int /*<<< orphan*/  B43_NTAB_TDI20A1 ; 
 int /*<<< orphan*/  B43_NTAB_TDI40A0 ; 
 int /*<<< orphan*/  B43_NTAB_TDI40A1 ; 
 int /*<<< orphan*/  B43_NTAB_TDTRN ; 
 int /*<<< orphan*/  B43_NTAB_TMAP ; 
 int /*<<< orphan*/  b43_ntab_adjustpower0 ; 
 int /*<<< orphan*/  b43_ntab_adjustpower1 ; 
 int /*<<< orphan*/  b43_ntab_bdi ; 
 int /*<<< orphan*/  b43_ntab_channelest ; 
 int /*<<< orphan*/  b43_ntab_estimatepowerlt0 ; 
 int /*<<< orphan*/  b43_ntab_estimatepowerlt1 ; 
 int /*<<< orphan*/  b43_ntab_framelookup ; 
 int /*<<< orphan*/  b43_ntab_framestruct ; 
 int /*<<< orphan*/  b43_ntab_gainctl0 ; 
 int /*<<< orphan*/  b43_ntab_gainctl1 ; 
 int /*<<< orphan*/  b43_ntab_intlevel ; 
 int /*<<< orphan*/  b43_ntab_iqlt0 ; 
 int /*<<< orphan*/  b43_ntab_iqlt1 ; 
 int /*<<< orphan*/  b43_ntab_loftlt0 ; 
 int /*<<< orphan*/  b43_ntab_loftlt1 ; 
 int /*<<< orphan*/  b43_ntab_mcs ; 
 int /*<<< orphan*/  b43_ntab_noisevar10 ; 
 int /*<<< orphan*/  b43_ntab_noisevar11 ; 
 int /*<<< orphan*/  b43_ntab_pilot ; 
 int /*<<< orphan*/  b43_ntab_pilotlt ; 
 int /*<<< orphan*/  b43_ntab_tdi20a0 ; 
 int /*<<< orphan*/  b43_ntab_tdi20a1 ; 
 int /*<<< orphan*/  b43_ntab_tdi40a0 ; 
 int /*<<< orphan*/  b43_ntab_tdi40a1 ; 
 int /*<<< orphan*/  b43_ntab_tdtrn ; 
 int /*<<< orphan*/  b43_ntab_tmap ; 
 int /*<<< orphan*/  ntab_upload (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_nphy_tables_init_rev0(struct b43_wldev *dev)
{
	/* Static tables */
	ntab_upload(dev, B43_NTAB_FRAMESTRUCT, b43_ntab_framestruct);
	ntab_upload(dev, B43_NTAB_FRAMELT, b43_ntab_framelookup);
	ntab_upload(dev, B43_NTAB_TMAP, b43_ntab_tmap);
	ntab_upload(dev, B43_NTAB_TDTRN, b43_ntab_tdtrn);
	ntab_upload(dev, B43_NTAB_INTLEVEL, b43_ntab_intlevel);
	ntab_upload(dev, B43_NTAB_PILOT, b43_ntab_pilot);
	ntab_upload(dev, B43_NTAB_TDI20A0, b43_ntab_tdi20a0);
	ntab_upload(dev, B43_NTAB_TDI20A1, b43_ntab_tdi20a1);
	ntab_upload(dev, B43_NTAB_TDI40A0, b43_ntab_tdi40a0);
	ntab_upload(dev, B43_NTAB_TDI40A1, b43_ntab_tdi40a1);
	ntab_upload(dev, B43_NTAB_CHANEST, b43_ntab_channelest);
	ntab_upload(dev, B43_NTAB_MCS, b43_ntab_mcs);
	ntab_upload(dev, B43_NTAB_NOISEVAR10, b43_ntab_noisevar10);
	ntab_upload(dev, B43_NTAB_NOISEVAR11, b43_ntab_noisevar11);

	/* Volatile tables */
	ntab_upload(dev, B43_NTAB_BDI, b43_ntab_bdi);
	ntab_upload(dev, B43_NTAB_PILOTLT, b43_ntab_pilotlt);
	ntab_upload(dev, B43_NTAB_C0_GAINCTL, b43_ntab_gainctl0);
	ntab_upload(dev, B43_NTAB_C1_GAINCTL, b43_ntab_gainctl1);
	ntab_upload(dev, B43_NTAB_C0_ESTPLT, b43_ntab_estimatepowerlt0);
	ntab_upload(dev, B43_NTAB_C1_ESTPLT, b43_ntab_estimatepowerlt1);
	ntab_upload(dev, B43_NTAB_C0_ADJPLT, b43_ntab_adjustpower0);
	ntab_upload(dev, B43_NTAB_C1_ADJPLT, b43_ntab_adjustpower1);
	ntab_upload(dev, B43_NTAB_C0_IQLT, b43_ntab_iqlt0);
	ntab_upload(dev, B43_NTAB_C1_IQLT, b43_ntab_iqlt1);
	ntab_upload(dev, B43_NTAB_C0_LOFEEDTH, b43_ntab_loftlt0);
	ntab_upload(dev, B43_NTAB_C1_LOFEEDTH, b43_ntab_loftlt1);
}