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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_vif {scalar_t__ type; scalar_t__ drv_priv; } ;
struct ath_vif {scalar_t__ primary_sta_vif; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  ath9k_set_assoc_state (struct ath_softc*,struct ieee80211_vif*) ; 

__attribute__((used)) static void ath9k_sta_vif_iter(void *data, u8 *mac, struct ieee80211_vif *vif)
{
	struct ath_softc *sc = data;
	struct ath_vif *avp = (void *)vif->drv_priv;

	if (vif->type != NL80211_IFTYPE_STATION)
		return;

	if (avp->primary_sta_vif)
		ath9k_set_assoc_state(sc, vif);
}