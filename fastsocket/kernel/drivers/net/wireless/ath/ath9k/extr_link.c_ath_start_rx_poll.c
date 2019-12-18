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
typedef  int u8 ;
struct TYPE_2__ {int beacon_interval; } ;
struct ath_softc {TYPE_1__ cur_beacon_conf; int /*<<< orphan*/  rx_poll_timer; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_SREV_9300 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_OP_PRIM_STA_VIF ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath_start_rx_poll(struct ath_softc *sc, u8 nbeacon)
{
	if (!AR_SREV_9300(sc->sc_ah))
		return;

	if (!test_bit(SC_OP_PRIM_STA_VIF, &sc->sc_flags))
		return;

	mod_timer(&sc->rx_poll_timer, jiffies + msecs_to_jiffies
		  (nbeacon * sc->cur_beacon_conf.beacon_interval));
}