#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct ath_beacon_config {scalar_t__ beacon_interval; } ;
struct ath_softc {TYPE_2__* sc_ah; struct ath_beacon_config cur_beacon_conf; } ;
struct ath_common {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sw_beacon_response_time; } ;
struct TYPE_5__ {scalar_t__ opmode; TYPE_1__ config; } ;

/* Variables and functions */
 int ATH_BCBUF ; 
 int ATH_DEFAULT_BINTVAL ; 
 int /*<<< orphan*/  BEACON ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int TSF_TO_TU (int,int) ; 
 scalar_t__ TU_TO_USEC (int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (TYPE_2__*) ; 
 int ath9k_hw_gettsf64 (TYPE_2__*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int ath9k_beacon_choose_slot(struct ath_softc *sc)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_beacon_config *cur_conf = &sc->cur_beacon_conf;
	u16 intval;
	u32 tsftu;
	u64 tsf;
	int slot;

	if (sc->sc_ah->opmode != NL80211_IFTYPE_AP) {
		ath_dbg(common, BEACON, "slot 0, tsf: %llu\n",
			ath9k_hw_gettsf64(sc->sc_ah));
		return 0;
	}

	intval = cur_conf->beacon_interval ? : ATH_DEFAULT_BINTVAL;
	tsf = ath9k_hw_gettsf64(sc->sc_ah);
	tsf += TU_TO_USEC(sc->sc_ah->config.sw_beacon_response_time);
	tsftu = TSF_TO_TU((tsf * ATH_BCBUF) >>32, tsf * ATH_BCBUF);
	slot = (tsftu % (intval * ATH_BCBUF)) / intval;

	ath_dbg(common, BEACON, "slot: %d tsf: %llu tsftu: %u\n",
		slot, tsf, tsftu / ATH_BCBUF);

	return slot;
}