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
struct cphy {int dummy; } ;

/* Variables and functions */
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int G_PSSR_SPEED (int) ; 
 int /*<<< orphan*/  MV88E1XXX_SPECIFIC_STATUS_REGISTER ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int V_PSSR_DUPLEX ; 
 int V_PSSR_LINK ; 
 int V_PSSR_RX_PAUSE ; 
 int V_PSSR_STATUS_RESOLVED ; 
 int V_PSSR_TX_PAUSE ; 
 int /*<<< orphan*/  simple_mdio_read (struct cphy*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int mv88e1xxx_get_link_status(struct cphy *cphy, int *link_ok,
				     int *speed, int *duplex, int *fc)
{
	u32 status;
	int sp = -1, dplx = -1, pause = 0;

	(void) simple_mdio_read(cphy,
			MV88E1XXX_SPECIFIC_STATUS_REGISTER, &status);
	if ((status & V_PSSR_STATUS_RESOLVED) != 0) {
		if (status & V_PSSR_RX_PAUSE)
			pause |= PAUSE_RX;
		if (status & V_PSSR_TX_PAUSE)
			pause |= PAUSE_TX;
		dplx = (status & V_PSSR_DUPLEX) ? DUPLEX_FULL : DUPLEX_HALF;
		sp = G_PSSR_SPEED(status);
		if (sp == 0)
			sp = SPEED_10;
		else if (sp == 1)
			sp = SPEED_100;
		else
			sp = SPEED_1000;
	}
	if (link_ok)
		*link_ok = (status & V_PSSR_LINK) != 0;
	if (speed)
		*speed = sp;
	if (duplex)
		*duplex = dplx;
	if (fc)
		*fc = pause;
	return 0;
}