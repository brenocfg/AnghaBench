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

/* Variables and functions */
#define  PHY_TYPE_BASET_10GB 134 
#define  PHY_TYPE_BASET_1GB 133 
#define  PHY_TYPE_BASEX_1GB 132 
#define  PHY_TYPE_SFP_1GB 131 
#define  PHY_TYPE_SFP_PLUS_10GB 130 
#define  PHY_TYPE_SGMII 129 
#define  PHY_TYPE_XFP_10GB 128 
 int PORT_DA ; 
 int PORT_FIBRE ; 
 int PORT_OTHER ; 
 int PORT_TP ; 

__attribute__((used)) static u32 be_get_port_type(u32 phy_type, u32 dac_cable_len)
{
	u32 port;

	switch (phy_type) {
	case PHY_TYPE_BASET_1GB:
	case PHY_TYPE_BASEX_1GB:
	case PHY_TYPE_SGMII:
		port = PORT_TP;
		break;
	case PHY_TYPE_SFP_PLUS_10GB:
		port = dac_cable_len ? PORT_DA : PORT_FIBRE;
		break;
	case PHY_TYPE_XFP_10GB:
	case PHY_TYPE_SFP_1GB:
		port = PORT_FIBRE;
		break;
	case PHY_TYPE_BASET_10GB:
		port = PORT_TP;
		break;
	default:
		port = PORT_OTHER;
	}

	return port;
}