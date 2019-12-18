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
typedef  int uint64_t ;
struct sbmac_softc {int sbm_speed; scalar_t__ sbm_state; int /*<<< orphan*/  sbm_maccfg; int /*<<< orphan*/  sbm_framecfg; } ;
typedef  enum sbmac_speed { ____Placeholder_sbmac_speed } sbmac_speed ;

/* Variables and functions */
 int K_MAC_IFG_THRSH_10 ; 
 int M_MAC_BURST_EN ; 
 int M_MAC_IFG_RX ; 
 int M_MAC_IFG_THRSH ; 
 int M_MAC_IFG_TX ; 
 int M_MAC_SLOT_SIZE ; 
 int M_MAC_SPEED_SEL ; 
 int V_MAC_IFG_RX_10 ; 
 int V_MAC_IFG_RX_100 ; 
 int V_MAC_IFG_RX_1000 ; 
 int V_MAC_IFG_THRSH_100 ; 
 int V_MAC_IFG_THRSH_1000 ; 
 int V_MAC_IFG_TX_10 ; 
 int V_MAC_IFG_TX_100 ; 
 int V_MAC_IFG_TX_1000 ; 
 int V_MAC_SLOT_SIZE_10 ; 
 int V_MAC_SLOT_SIZE_100 ; 
 int V_MAC_SLOT_SIZE_1000 ; 
 int V_MAC_SPEED_SEL_1000MBPS ; 
 int V_MAC_SPEED_SEL_100MBPS ; 
 int V_MAC_SPEED_SEL_10MBPS ; 
 int __raw_readq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 
#define  sbmac_speed_10 130 
#define  sbmac_speed_100 129 
#define  sbmac_speed_1000 128 
 scalar_t__ sbmac_state_on ; 

__attribute__((used)) static int sbmac_set_speed(struct sbmac_softc *s, enum sbmac_speed speed)
{
	uint64_t cfg;
	uint64_t framecfg;

	/*
	 * Save new current values
	 */

	s->sbm_speed = speed;

	if (s->sbm_state == sbmac_state_on)
		return 0;	/* save for next restart */

	/*
	 * Read current register values
	 */

	cfg = __raw_readq(s->sbm_maccfg);
	framecfg = __raw_readq(s->sbm_framecfg);

	/*
	 * Mask out the stuff we want to change
	 */

	cfg &= ~(M_MAC_BURST_EN | M_MAC_SPEED_SEL);
	framecfg &= ~(M_MAC_IFG_RX | M_MAC_IFG_TX | M_MAC_IFG_THRSH |
		      M_MAC_SLOT_SIZE);

	/*
	 * Now add in the new bits
	 */

	switch (speed) {
	case sbmac_speed_10:
		framecfg |= V_MAC_IFG_RX_10 |
			V_MAC_IFG_TX_10 |
			K_MAC_IFG_THRSH_10 |
			V_MAC_SLOT_SIZE_10;
		cfg |= V_MAC_SPEED_SEL_10MBPS;
		break;

	case sbmac_speed_100:
		framecfg |= V_MAC_IFG_RX_100 |
			V_MAC_IFG_TX_100 |
			V_MAC_IFG_THRSH_100 |
			V_MAC_SLOT_SIZE_100;
		cfg |= V_MAC_SPEED_SEL_100MBPS ;
		break;

	case sbmac_speed_1000:
		framecfg |= V_MAC_IFG_RX_1000 |
			V_MAC_IFG_TX_1000 |
			V_MAC_IFG_THRSH_1000 |
			V_MAC_SLOT_SIZE_1000;
		cfg |= V_MAC_SPEED_SEL_1000MBPS | M_MAC_BURST_EN;
		break;

	default:
		return 0;
	}

	/*
	 * Send the bits back to the hardware
	 */

	__raw_writeq(framecfg, s->sbm_framecfg);
	__raw_writeq(cfg, s->sbm_maccfg);

	return 1;
}