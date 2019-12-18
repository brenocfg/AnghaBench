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
struct soc_pcmcia_socket {scalar_t__ nr; } ;
struct pcmcia_state {int detect; int ready; int bvd1; int bvd2; int vs_3v; int vs_Xv; scalar_t__ wrprot; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAINSTONE_S0_STSCHG_IRQ ; 
 int /*<<< orphan*/  MAINSTONE_S1_STSCHG_IRQ ; 
 unsigned long MST_PCMCIA0 ; 
 unsigned long MST_PCMCIA1 ; 
 unsigned long MST_PCMCIA_nCD ; 
 unsigned long MST_PCMCIA_nIRQ ; 
 unsigned long MST_PCMCIA_nSPKR_BVD2 ; 
 unsigned long MST_PCMCIA_nSTSCHG_BVD1 ; 
 unsigned long MST_PCMCIA_nVS1 ; 
 unsigned long MST_PCMCIA_nVS2 ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 unsigned long* mst_pcmcia_status ; 

__attribute__((used)) static void mst_pcmcia_socket_state(struct soc_pcmcia_socket *skt,
				    struct pcmcia_state *state)
{
	unsigned long status, flip;

	status = (skt->nr == 0) ? MST_PCMCIA0 : MST_PCMCIA1;
	flip = (status ^ mst_pcmcia_status[skt->nr]) & MST_PCMCIA_nSTSCHG_BVD1;

	/*
	 * Workaround for STSCHG which can't be deasserted:
	 * We therefore disable/enable corresponding IRQs
	 * as needed to avoid IRQ locks.
	 */
	if (flip) {
		mst_pcmcia_status[skt->nr] = status;
		if (status & MST_PCMCIA_nSTSCHG_BVD1)
			enable_irq( (skt->nr == 0) ? MAINSTONE_S0_STSCHG_IRQ
						   : MAINSTONE_S1_STSCHG_IRQ );
		else
			disable_irq( (skt->nr == 0) ? MAINSTONE_S0_STSCHG_IRQ
						    : MAINSTONE_S1_STSCHG_IRQ );
	}

	state->detect = (status & MST_PCMCIA_nCD) ? 0 : 1;
	state->ready  = (status & MST_PCMCIA_nIRQ) ? 1 : 0;
	state->bvd1   = (status & MST_PCMCIA_nSTSCHG_BVD1) ? 1 : 0;
	state->bvd2   = (status & MST_PCMCIA_nSPKR_BVD2) ? 1 : 0;
	state->vs_3v  = (status & MST_PCMCIA_nVS1) ? 0 : 1;
	state->vs_Xv  = (status & MST_PCMCIA_nVS2) ? 0 : 1;
	state->wrprot = 0;  /* not available */
}