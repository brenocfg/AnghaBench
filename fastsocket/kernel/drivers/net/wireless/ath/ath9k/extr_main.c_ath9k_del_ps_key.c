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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {scalar_t__ drv_priv; } ;
struct ieee80211_key_conf {scalar_t__ hw_key_idx; } ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;
struct ath_node {scalar_t__ ps_key; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_key_delete (struct ath_common*,struct ieee80211_key_conf*) ; 

__attribute__((used)) static void ath9k_del_ps_key(struct ath_softc *sc,
			     struct ieee80211_vif *vif,
			     struct ieee80211_sta *sta)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_node *an = (struct ath_node *) sta->drv_priv;
	struct ieee80211_key_conf ps_key = { .hw_key_idx = an->ps_key };

	if (!an->ps_key)
	    return;

	ath_key_delete(common, &ps_key);
	an->ps_key = 0;
}