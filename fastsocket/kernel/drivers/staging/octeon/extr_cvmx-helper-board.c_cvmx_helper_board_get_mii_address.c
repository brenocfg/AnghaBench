#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_BBGW_REF 149 
#define  CVMX_BOARD_TYPE_CN3005_EVB_HS5 148 
#define  CVMX_BOARD_TYPE_CN3010_EVB_HS5 147 
#define  CVMX_BOARD_TYPE_CN3020_EVB_HS5 146 
#define  CVMX_BOARD_TYPE_CUST_NB5 145 
#define  CVMX_BOARD_TYPE_EBH3000 144 
#define  CVMX_BOARD_TYPE_EBH3100 143 
#define  CVMX_BOARD_TYPE_EBH5200 142 
#define  CVMX_BOARD_TYPE_EBH5201 141 
#define  CVMX_BOARD_TYPE_EBH5600 140 
#define  CVMX_BOARD_TYPE_EBH5601 139 
#define  CVMX_BOARD_TYPE_EBH5610 138 
#define  CVMX_BOARD_TYPE_EBT3000 137 
#define  CVMX_BOARD_TYPE_EBT5200 136 
#define  CVMX_BOARD_TYPE_EBT5800 135 
#define  CVMX_BOARD_TYPE_HIKARI 134 
#define  CVMX_BOARD_TYPE_KODAMA 133 
#define  CVMX_BOARD_TYPE_NAC38 132 
#define  CVMX_BOARD_TYPE_NICPRO2 131 
#define  CVMX_BOARD_TYPE_NIC_XLE_4G 130 
#define  CVMX_BOARD_TYPE_SIM 129 
#define  CVMX_BOARD_TYPE_THUNDER 128 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

int cvmx_helper_board_get_mii_address(int ipd_port)
{
	switch (cvmx_sysinfo_get()->board_type) {
	case CVMX_BOARD_TYPE_SIM:
		/* Simulator doesn't have MII */
		return -1;
	case CVMX_BOARD_TYPE_EBT3000:
	case CVMX_BOARD_TYPE_EBT5800:
	case CVMX_BOARD_TYPE_THUNDER:
	case CVMX_BOARD_TYPE_NICPRO2:
		/* Interface 0 is SPI4, interface 1 is RGMII */
		if ((ipd_port >= 16) && (ipd_port < 20))
			return ipd_port - 16;
		else
			return -1;
	case CVMX_BOARD_TYPE_KODAMA:
	case CVMX_BOARD_TYPE_EBH3100:
	case CVMX_BOARD_TYPE_HIKARI:
	case CVMX_BOARD_TYPE_CN3010_EVB_HS5:
	case CVMX_BOARD_TYPE_CN3005_EVB_HS5:
	case CVMX_BOARD_TYPE_CN3020_EVB_HS5:
		/*
		 * Port 0 is WAN connected to a PHY, Port 1 is GMII
		 * connected to a switch
		 */
		if (ipd_port == 0)
			return 4;
		else if (ipd_port == 1)
			return 9;
		else
			return -1;
	case CVMX_BOARD_TYPE_NAC38:
		/* Board has 8 RGMII ports PHYs are 0-7 */
		if ((ipd_port >= 0) && (ipd_port < 4))
			return ipd_port;
		else if ((ipd_port >= 16) && (ipd_port < 20))
			return ipd_port - 16 + 4;
		else
			return -1;
	case CVMX_BOARD_TYPE_EBH3000:
		/* Board has dual SPI4 and no PHYs */
		return -1;
	case CVMX_BOARD_TYPE_EBH5200:
	case CVMX_BOARD_TYPE_EBH5201:
	case CVMX_BOARD_TYPE_EBT5200:
		/*
		 * Board has 4 SGMII ports. The PHYs start right after the MII
		 * ports MII0 = 0, MII1 = 1, SGMII = 2-5.
		 */
		if ((ipd_port >= 0) && (ipd_port < 4))
			return ipd_port + 2;
		else
			return -1;
	case CVMX_BOARD_TYPE_EBH5600:
	case CVMX_BOARD_TYPE_EBH5601:
	case CVMX_BOARD_TYPE_EBH5610:
		/*
		 * Board has 8 SGMII ports. 4 connect out, two connect
		 * to a switch, and 2 loop to each other
		 */
		if ((ipd_port >= 0) && (ipd_port < 4))
			return ipd_port + 1;
		else
			return -1;
	case CVMX_BOARD_TYPE_CUST_NB5:
		if (ipd_port == 2)
			return 4;
		else
			return -1;
	case CVMX_BOARD_TYPE_NIC_XLE_4G:
		/* Board has 4 SGMII ports. connected QLM3(interface 1) */
		if ((ipd_port >= 16) && (ipd_port < 20))
			return ipd_port - 16 + 1;
		else
			return -1;
	case CVMX_BOARD_TYPE_BBGW_REF:
		/*
		 * No PHYs are connected to Octeon, everything is
		 * through switch.
		 */
		return -1;
	}

	/* Some unknown board. Somebody forgot to update this function... */
	cvmx_dprintf
	    ("cvmx_helper_board_get_mii_address: Unknown board type %d\n",
	     cvmx_sysinfo_get()->board_type);
	return -1;
}