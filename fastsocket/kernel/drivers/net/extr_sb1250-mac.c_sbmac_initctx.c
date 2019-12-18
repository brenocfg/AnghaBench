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
struct sbmac_softc {int /*<<< orphan*/  sbm_state; int /*<<< orphan*/  sbm_rxdma; int /*<<< orphan*/  sbm_txdma; scalar_t__ sbm_base; scalar_t__ sbm_mdio; scalar_t__ sbm_imr; scalar_t__ sbm_isr; scalar_t__ sbm_rxfilter; scalar_t__ sbm_framecfg; scalar_t__ sbm_fifocfg; scalar_t__ sbm_maccfg; scalar_t__ sbm_macenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RX ; 
 int /*<<< orphan*/  DMA_TX ; 
 scalar_t__ R_MAC_ADFILTER_CFG ; 
 scalar_t__ R_MAC_CFG ; 
 scalar_t__ R_MAC_ENABLE ; 
 scalar_t__ R_MAC_FRAMECFG ; 
 scalar_t__ R_MAC_INT_MASK ; 
 scalar_t__ R_MAC_MDIO ; 
 scalar_t__ R_MAC_STATUS ; 
 scalar_t__ R_MAC_THRSH_CFG ; 
 int /*<<< orphan*/  SBMAC_MAX_RXDESCR ; 
 int /*<<< orphan*/  SBMAC_MAX_TXDESCR ; 
 int /*<<< orphan*/  sbdma_initctx (int /*<<< orphan*/ *,struct sbmac_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbmac_state_off ; 

__attribute__((used)) static int sbmac_initctx(struct sbmac_softc *s)
{

	/*
	 * figure out the addresses of some ports
	 */

	s->sbm_macenable = s->sbm_base + R_MAC_ENABLE;
	s->sbm_maccfg    = s->sbm_base + R_MAC_CFG;
	s->sbm_fifocfg   = s->sbm_base + R_MAC_THRSH_CFG;
	s->sbm_framecfg  = s->sbm_base + R_MAC_FRAMECFG;
	s->sbm_rxfilter  = s->sbm_base + R_MAC_ADFILTER_CFG;
	s->sbm_isr       = s->sbm_base + R_MAC_STATUS;
	s->sbm_imr       = s->sbm_base + R_MAC_INT_MASK;
	s->sbm_mdio      = s->sbm_base + R_MAC_MDIO;

	/*
	 * Initialize the DMA channels.  Right now, only one per MAC is used
	 * Note: Only do this _once_, as it allocates memory from the kernel!
	 */

	sbdma_initctx(&(s->sbm_txdma),s,0,DMA_TX,SBMAC_MAX_TXDESCR);
	sbdma_initctx(&(s->sbm_rxdma),s,0,DMA_RX,SBMAC_MAX_RXDESCR);

	/*
	 * initial state is OFF
	 */

	s->sbm_state = sbmac_state_off;

	return 0;
}