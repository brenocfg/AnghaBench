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
struct sk_buff {int len; } ;
struct ath_softc {int ps_flags; int /*<<< orphan*/  sc_ah; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PS ; 
 int PS_BEACON_SYNC ; 
 int PS_WAIT_FOR_BEACON ; 
 int PS_WAIT_FOR_CAB ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_set_beacon (struct ath_softc*) ; 
 scalar_t__ ath_beacon_dtim_pending_cab (struct sk_buff*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ath_rx_ps_beacon(struct ath_softc *sc, struct sk_buff *skb)
{
	struct ath_common *common = ath9k_hw_common(sc->sc_ah);

	if (skb->len < 24 + 8 + 2 + 2)
		return;

	sc->ps_flags &= ~PS_WAIT_FOR_BEACON;

	if (sc->ps_flags & PS_BEACON_SYNC) {
		sc->ps_flags &= ~PS_BEACON_SYNC;
		ath_dbg(common, PS,
			"Reconfigure beacon timers based on synchronized timestamp\n");
		ath9k_set_beacon(sc);
	}

	if (ath_beacon_dtim_pending_cab(skb)) {
		/*
		 * Remain awake waiting for buffered broadcast/multicast
		 * frames. If the last broadcast/multicast frame is not
		 * received properly, the next beacon frame will work as
		 * a backup trigger for returning into NETWORK SLEEP state,
		 * so we are waiting for it as well.
		 */
		ath_dbg(common, PS,
			"Received DTIM beacon indicating buffered broadcast/multicast frame(s)\n");
		sc->ps_flags |= PS_WAIT_FOR_CAB | PS_WAIT_FOR_BEACON;
		return;
	}

	if (sc->ps_flags & PS_WAIT_FOR_CAB) {
		/*
		 * This can happen if a broadcast frame is dropped or the AP
		 * fails to send a frame indicating that all CAB frames have
		 * been delivered.
		 */
		sc->ps_flags &= ~PS_WAIT_FOR_CAB;
		ath_dbg(common, PS, "PS wait for CAB frames timed out\n");
	}
}