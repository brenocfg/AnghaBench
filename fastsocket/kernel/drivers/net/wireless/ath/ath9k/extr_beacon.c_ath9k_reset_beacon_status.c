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
struct TYPE_2__ {int tx_processed; int tx_last; } ;
struct ath_softc {TYPE_1__ beacon; } ;

/* Variables and functions */

__attribute__((used)) static void ath9k_reset_beacon_status(struct ath_softc *sc)
{
	sc->beacon.tx_processed = false;
	sc->beacon.tx_last = false;
}