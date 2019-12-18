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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int ADVERTISE_1000XPAUSE ; 
 int ADVERTISE_1000XPSE_ASYM ; 
 int FLOW_CTRL_RX ; 
 int FLOW_CTRL_TX ; 

__attribute__((used)) static u8 tg3_resolve_flowctrl_1000X(u16 lcladv, u16 rmtadv)
{
	u8 cap = 0;

	if (lcladv & rmtadv & ADVERTISE_1000XPAUSE) {
		cap = FLOW_CTRL_TX | FLOW_CTRL_RX;
	} else if (lcladv & rmtadv & ADVERTISE_1000XPSE_ASYM) {
		if (lcladv & ADVERTISE_1000XPAUSE)
			cap = FLOW_CTRL_RX;
		if (rmtadv & ADVERTISE_1000XPAUSE)
			cap = FLOW_CTRL_TX;
	}

	return cap;
}