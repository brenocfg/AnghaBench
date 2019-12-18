#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * rxlink; } ;
struct ath_softc {struct ath_hw* sc_ah; TYPE_2__ rx; } ;
struct TYPE_3__ {int hw_caps; } ;
struct ath_hw {int ah_flags; TYPE_1__ caps; } ;

/* Variables and functions */
 int AH_UNPLUGGED ; 
 int ATH9K_HW_CAP_EDMA ; 
 int /*<<< orphan*/  ATH_DBG_WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ath9k_hw_abortpcurecv (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_setrxfilter (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int ath9k_hw_stopdmarecv (struct ath_hw*,int*) ; 
 int /*<<< orphan*/  ath_edma_stop_recv (struct ath_softc*) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath_flushrecv (struct ath_softc*) ; 
 scalar_t__ unlikely (int) ; 

bool ath_stoprecv(struct ath_softc *sc)
{
	struct ath_hw *ah = sc->sc_ah;
	bool stopped, reset = false;

	ath9k_hw_abortpcurecv(ah);
	ath9k_hw_setrxfilter(ah, 0);
	stopped = ath9k_hw_stopdmarecv(ah, &reset);

	ath_flushrecv(sc);

	if (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ath_edma_stop_recv(sc);
	else
		sc->rx.rxlink = NULL;

	if (!(ah->ah_flags & AH_UNPLUGGED) &&
	    unlikely(!stopped)) {
		ath_err(ath9k_hw_common(sc->sc_ah),
			"Could not stop RX, we could be "
			"confusing the DMA engine when we start RX up\n");
		ATH_DBG_WARN_ON_ONCE(!stopped);
	}
	return stopped && !reset;
}