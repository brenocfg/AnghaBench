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
struct sbmac_softc {scalar_t__ sbm_state; int /*<<< orphan*/  sbm_txdma; int /*<<< orphan*/  sbm_rxdma; int /*<<< orphan*/  sbm_macenable; int /*<<< orphan*/  sbm_imr; int /*<<< orphan*/  sbm_rxfilter; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writeq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbdma_channel_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbdma_emptyring (int /*<<< orphan*/ *) ; 
 scalar_t__ sbmac_state_off ; 

__attribute__((used)) static void sbmac_channel_stop(struct sbmac_softc *s)
{
	/* don't do this if already stopped */

	if (s->sbm_state == sbmac_state_off)
		return;

	/* don't accept any packets, disable all interrupts */

	__raw_writeq(0, s->sbm_rxfilter);
	__raw_writeq(0, s->sbm_imr);

	/* Turn off ticker */

	/* XXX */

	/* turn off receiver and transmitter */

	__raw_writeq(0, s->sbm_macenable);

	/* We're stopped now. */

	s->sbm_state = sbmac_state_off;

	/*
	 * Stop DMA channels (rings should be ok now)
	 */

	sbdma_channel_stop(&(s->sbm_rxdma));
	sbdma_channel_stop(&(s->sbm_txdma));

	/* Empty the receive and transmit rings */

	sbdma_emptyring(&(s->sbm_rxdma));
	sbdma_emptyring(&(s->sbm_txdma));

}