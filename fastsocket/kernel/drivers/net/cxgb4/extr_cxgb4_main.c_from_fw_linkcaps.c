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

/* Variables and functions */
 unsigned int FW_PORT_CAP_ANEG ; 
 unsigned int FW_PORT_CAP_SPEED_100M ; 
 unsigned int FW_PORT_CAP_SPEED_10G ; 
 unsigned int FW_PORT_CAP_SPEED_1G ; 
 unsigned int FW_PORT_TYPE_BP4_AP ; 
 unsigned int FW_PORT_TYPE_BP_AP ; 
 unsigned int FW_PORT_TYPE_BT_SGMII ; 
 unsigned int FW_PORT_TYPE_BT_XAUI ; 
 unsigned int FW_PORT_TYPE_BT_XFI ; 
 unsigned int FW_PORT_TYPE_FIBER_XAUI ; 
 unsigned int FW_PORT_TYPE_FIBER_XFI ; 
 unsigned int FW_PORT_TYPE_KR ; 
 unsigned int FW_PORT_TYPE_KX ; 
 unsigned int FW_PORT_TYPE_KX4 ; 
 unsigned int FW_PORT_TYPE_SFP ; 
 unsigned int SUPPORTED_10000baseKR_Full ; 
 unsigned int SUPPORTED_10000baseKX4_Full ; 
 unsigned int SUPPORTED_10000baseR_FEC ; 
 unsigned int SUPPORTED_10000baseT_Full ; 
 unsigned int SUPPORTED_1000baseKX_Full ; 
 unsigned int SUPPORTED_1000baseT_Full ; 
 unsigned int SUPPORTED_100baseT_Full ; 
 unsigned int SUPPORTED_Autoneg ; 
 unsigned int SUPPORTED_Backplane ; 
 unsigned int SUPPORTED_FIBRE ; 
 unsigned int SUPPORTED_TP ; 

__attribute__((used)) static unsigned int from_fw_linkcaps(unsigned int type, unsigned int caps)
{
	unsigned int v = 0;

	if (type == FW_PORT_TYPE_BT_SGMII || type == FW_PORT_TYPE_BT_XFI ||
	    type == FW_PORT_TYPE_BT_XAUI) {
		v |= SUPPORTED_TP;
		if (caps & FW_PORT_CAP_SPEED_100M)
			v |= SUPPORTED_100baseT_Full;
		if (caps & FW_PORT_CAP_SPEED_1G)
			v |= SUPPORTED_1000baseT_Full;
		if (caps & FW_PORT_CAP_SPEED_10G)
			v |= SUPPORTED_10000baseT_Full;
	} else if (type == FW_PORT_TYPE_KX4 || type == FW_PORT_TYPE_KX) {
		v |= SUPPORTED_Backplane;
		if (caps & FW_PORT_CAP_SPEED_1G)
			v |= SUPPORTED_1000baseKX_Full;
		if (caps & FW_PORT_CAP_SPEED_10G)
			v |= SUPPORTED_10000baseKX4_Full;
	} else if (type == FW_PORT_TYPE_KR)
		v |= SUPPORTED_Backplane | SUPPORTED_10000baseKR_Full;
	else if (type == FW_PORT_TYPE_BP_AP)
		v |= SUPPORTED_Backplane | SUPPORTED_10000baseR_FEC |
		     SUPPORTED_10000baseKR_Full | SUPPORTED_1000baseKX_Full;
	else if (type == FW_PORT_TYPE_BP4_AP)
		v |= SUPPORTED_Backplane | SUPPORTED_10000baseR_FEC |
		     SUPPORTED_10000baseKR_Full | SUPPORTED_1000baseKX_Full |
		     SUPPORTED_10000baseKX4_Full;
	else if (type == FW_PORT_TYPE_FIBER_XFI ||
		 type == FW_PORT_TYPE_FIBER_XAUI || type == FW_PORT_TYPE_SFP)
		v |= SUPPORTED_FIBRE;

	if (caps & FW_PORT_CAP_ANEG)
		v |= SUPPORTED_Autoneg;
	return v;
}