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
struct sk_buff {int dummy; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_tx_control {int /*<<< orphan*/  txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  cabq; } ;
struct ath_softc {TYPE_1__ beacon; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMIT ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ath_tx_start (struct ieee80211_hw*,struct sk_buff*,struct ath_tx_control*) ; 
 int /*<<< orphan*/  ieee80211_free_txskb (struct ieee80211_hw*,struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct ath_tx_control*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath9k_tx_cabq(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct ath_softc *sc = hw->priv;
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);
	struct ath_tx_control txctl;

	memset(&txctl, 0, sizeof(struct ath_tx_control));
	txctl.txq = sc->beacon.cabq;

	ath_dbg(common, XMIT, "transmitting CABQ packet, skb: %p\n", skb);

	if (ath_tx_start(hw, skb, &txctl) != 0) {
		ath_dbg(common, XMIT, "CABQ TX failed\n");
		ieee80211_free_txskb(hw, skb);
	}
}