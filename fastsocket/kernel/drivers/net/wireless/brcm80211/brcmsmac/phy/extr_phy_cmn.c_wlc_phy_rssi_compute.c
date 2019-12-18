#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint ;
typedef  size_t u8 ;
struct d11rxhdr {int PhyRxStatus_1; int RxStatus2; int PhyRxStatus_2; } ;
struct brcms_phy_pub {scalar_t__ radioid; } ;
struct brcms_phy_lcnphy {int lcnphy_pkteng_rssi_slope; } ;
struct TYPE_4__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {TYPE_2__ u; TYPE_1__* sh; } ;
struct TYPE_3__ {int corerev; } ;

/* Variables and functions */
 scalar_t__ BCM2055_ID ; 
 scalar_t__ BCM2056_ID ; 
 scalar_t__ BCM2057_ID ; 
 int BRCMS_RSSI_INVALID ; 
 scalar_t__ ISLCNPHY (struct brcms_phy*) ; 
 int PRXS1_JSSI_MASK ; 
 int RXS_PHYRXST_VALID ; 
 int* lcnphy_gain_index_offset_for_pkt_rssi ; 
 int wlc_phy_rssi_compute_nphy (struct brcms_phy*,struct d11rxhdr*) ; 

int wlc_phy_rssi_compute(struct brcms_phy_pub *pih,
			 struct d11rxhdr *rxh)
{
	int rssi = rxh->PhyRxStatus_1 & PRXS1_JSSI_MASK;
	uint radioid = pih->radioid;
	struct brcms_phy *pi = (struct brcms_phy *) pih;

	if ((pi->sh->corerev >= 11)
	    && !(rxh->RxStatus2 & RXS_PHYRXST_VALID)) {
		rssi = BRCMS_RSSI_INVALID;
		goto end;
	}

	if (ISLCNPHY(pi)) {
		u8 gidx = (rxh->PhyRxStatus_2 & 0xFC00) >> 10;
		struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;

		if (rssi > 127)
			rssi -= 256;

		rssi = rssi + lcnphy_gain_index_offset_for_pkt_rssi[gidx];
		if ((rssi > -46) && (gidx > 18))
			rssi = rssi + 7;

		rssi = rssi + pi_lcn->lcnphy_pkteng_rssi_slope;

		rssi = rssi + 2;

	}

	if (ISLCNPHY(pi)) {
		if (rssi > 127)
			rssi -= 256;
	} else if (radioid == BCM2055_ID || radioid == BCM2056_ID
		   || radioid == BCM2057_ID) {
		rssi = wlc_phy_rssi_compute_nphy(pi, rxh);
	}

end:
	return rssi;
}