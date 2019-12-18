#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int rxfilter; } ;
struct ath_softc {int nvifs; TYPE_5__* sc_ah; TYPE_2__ rx; TYPE_1__* hw; } ;
struct TYPE_8__ {scalar_t__ macVersion; } ;
struct TYPE_10__ {scalar_t__ opmode; TYPE_3__ hw_version; scalar_t__ is_monitoring; } ;
struct TYPE_9__ {scalar_t__ radar_enabled; } ;
struct TYPE_6__ {TYPE_4__ conf; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9550 (TYPE_5__*) ; 
 scalar_t__ AR_SREV_VERSION_9160 ; 
 int ATH9K_RX_FILTER_4ADDRESS ; 
 int ATH9K_RX_FILTER_BCAST ; 
 int ATH9K_RX_FILTER_BEACON ; 
 int ATH9K_RX_FILTER_COMP_BAR ; 
 int ATH9K_RX_FILTER_CONTROL ; 
 int ATH9K_RX_FILTER_MCAST ; 
 int ATH9K_RX_FILTER_MCAST_BCAST_ALL ; 
 int ATH9K_RX_FILTER_MYBEACON ; 
 int ATH9K_RX_FILTER_PHYERR ; 
 int ATH9K_RX_FILTER_PHYRADAR ; 
 int ATH9K_RX_FILTER_PROBEREQ ; 
 int ATH9K_RX_FILTER_PROM ; 
 int ATH9K_RX_FILTER_PSPOLL ; 
 int ATH9K_RX_FILTER_UCAST ; 
 int FIF_BCN_PRBRESP_PROMISC ; 
 int FIF_CONTROL ; 
 int FIF_OTHER_BSS ; 
 int FIF_PROBE_REQ ; 
 int FIF_PSPOLL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 scalar_t__ conf_is_ht (TYPE_4__*) ; 

u32 ath_calcrxfilter(struct ath_softc *sc)
{
	u32 rfilt;

	rfilt = ATH9K_RX_FILTER_UCAST | ATH9K_RX_FILTER_BCAST
		| ATH9K_RX_FILTER_MCAST;

	/* if operating on a DFS channel, enable radar pulse detection */
	if (sc->hw->conf.radar_enabled)
		rfilt |= ATH9K_RX_FILTER_PHYRADAR | ATH9K_RX_FILTER_PHYERR;

	if (sc->rx.rxfilter & FIF_PROBE_REQ)
		rfilt |= ATH9K_RX_FILTER_PROBEREQ;

	/*
	 * Set promiscuous mode when FIF_PROMISC_IN_BSS is enabled for station
	 * mode interface or when in monitor mode. AP mode does not need this
	 * since it receives all in-BSS frames anyway.
	 */
	if (sc->sc_ah->is_monitoring)
		rfilt |= ATH9K_RX_FILTER_PROM;

	if (sc->rx.rxfilter & FIF_CONTROL)
		rfilt |= ATH9K_RX_FILTER_CONTROL;

	if ((sc->sc_ah->opmode == NL80211_IFTYPE_STATION) &&
	    (sc->nvifs <= 1) &&
	    !(sc->rx.rxfilter & FIF_BCN_PRBRESP_PROMISC))
		rfilt |= ATH9K_RX_FILTER_MYBEACON;
	else
		rfilt |= ATH9K_RX_FILTER_BEACON;

	if ((sc->sc_ah->opmode == NL80211_IFTYPE_AP) ||
	    (sc->rx.rxfilter & FIF_PSPOLL))
		rfilt |= ATH9K_RX_FILTER_PSPOLL;

	if (conf_is_ht(&sc->hw->conf))
		rfilt |= ATH9K_RX_FILTER_COMP_BAR;

	if (sc->nvifs > 1 || (sc->rx.rxfilter & FIF_OTHER_BSS)) {
		/* This is needed for older chips */
		if (sc->sc_ah->hw_version.macVersion <= AR_SREV_VERSION_9160)
			rfilt |= ATH9K_RX_FILTER_PROM;
		rfilt |= ATH9K_RX_FILTER_MCAST_BCAST_ALL;
	}

	if (AR_SREV_9550(sc->sc_ah))
		rfilt |= ATH9K_RX_FILTER_4ADDRESS;

	return rfilt;

}