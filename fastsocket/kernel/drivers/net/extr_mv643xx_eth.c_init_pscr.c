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
typedef  int u32 ;
struct mv643xx_eth_private {int /*<<< orphan*/ * phy; } ;

/* Variables and functions */
 int DISABLE_AUTO_NEG_FOR_DUPLEX ; 
 int DISABLE_AUTO_NEG_FOR_FLOW_CTRL ; 
 int DISABLE_AUTO_NEG_SPEED_GMII ; 
 int DUPLEX_FULL ; 
 int MAX_RX_PACKET_9700BYTE ; 
 int /*<<< orphan*/  PORT_SERIAL_CONTROL ; 
 int SERIAL_PORT_CONTROL_RESERVED ; 
 int SERIAL_PORT_ENABLE ; 
 int SET_FULL_DUPLEX_MODE ; 
 int SET_GMII_SPEED_TO_1000 ; 
 int SET_MII_SPEED_TO_100 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_pscr(struct mv643xx_eth_private *mp, int speed, int duplex)
{
	u32 pscr;

	pscr = rdlp(mp, PORT_SERIAL_CONTROL);
	if (pscr & SERIAL_PORT_ENABLE) {
		pscr &= ~SERIAL_PORT_ENABLE;
		wrlp(mp, PORT_SERIAL_CONTROL, pscr);
	}

	pscr = MAX_RX_PACKET_9700BYTE | SERIAL_PORT_CONTROL_RESERVED;
	if (mp->phy == NULL) {
		pscr |= DISABLE_AUTO_NEG_SPEED_GMII;
		if (speed == SPEED_1000)
			pscr |= SET_GMII_SPEED_TO_1000;
		else if (speed == SPEED_100)
			pscr |= SET_MII_SPEED_TO_100;

		pscr |= DISABLE_AUTO_NEG_FOR_FLOW_CTRL;

		pscr |= DISABLE_AUTO_NEG_FOR_DUPLEX;
		if (duplex == DUPLEX_FULL)
			pscr |= SET_FULL_DUPLEX_MODE;
	}

	wrlp(mp, PORT_SERIAL_CONTROL, pscr);
}