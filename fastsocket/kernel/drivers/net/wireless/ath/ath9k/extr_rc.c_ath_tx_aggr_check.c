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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  ht_supported; } ;
struct ieee80211_sta {TYPE_1__ ht_cap; scalar_t__ drv_priv; } ;
struct ath_softc {int dummy; } ;
struct ath_node {int dummy; } ;
struct ath_atx_tid {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 struct ath_atx_tid* ATH_AN_2_TID (struct ath_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ath_tx_aggr_check(struct ath_softc *sc, struct ieee80211_sta *sta,
			      u8 tidno)
{
	struct ath_node *an = (struct ath_node *)sta->drv_priv;
	struct ath_atx_tid *txtid;

	if (!sta->ht_cap.ht_supported)
		return false;

	txtid = ATH_AN_2_TID(an, tidno);
	return !txtid->active;
}