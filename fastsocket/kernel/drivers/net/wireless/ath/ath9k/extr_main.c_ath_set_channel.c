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
struct ieee80211_hw {int dummy; } ;
struct ath_softc {int /*<<< orphan*/  sc_flags; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SC_OP_INVALID ; 
 int ath_reset_internal (struct ath_softc*,struct ath9k_channel*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath_set_channel(struct ath_softc *sc, struct ieee80211_hw *hw,
		    struct ath9k_channel *hchan)
{
	int r;

	if (test_bit(SC_OP_INVALID, &sc->sc_flags))
		return -EIO;

	r = ath_reset_internal(sc, hchan);

	return r;
}