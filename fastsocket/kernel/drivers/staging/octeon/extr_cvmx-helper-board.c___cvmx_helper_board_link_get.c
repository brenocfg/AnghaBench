#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int status; int duplex; int speed; } ;
union cvmx_gmxx_rxx_rx_inbnd {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
struct TYPE_8__ {int link_up; int full_duplex; int speed; } ;
struct TYPE_9__ {scalar_t__ u64; TYPE_2__ s; } ;
typedef  TYPE_3__ cvmx_helper_link_info_t ;
struct TYPE_10__ {int board_type; } ;

/* Variables and functions */
#define  CVMX_BOARD_TYPE_BBGW_REF 134 
#define  CVMX_BOARD_TYPE_CN3005_EVB_HS5 133 
#define  CVMX_BOARD_TYPE_CN3010_EVB_HS5 132 
#define  CVMX_BOARD_TYPE_CN3020_EVB_HS5 131 
#define  CVMX_BOARD_TYPE_CUST_NB5 130 
#define  CVMX_BOARD_TYPE_EBH3100 129 
#define  CVMX_BOARD_TYPE_SIM 128 
 int /*<<< orphan*/  CVMX_GMXX_RXX_RX_INBND (int,int) ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_CN50XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int cvmx_helper_board_get_mii_address (int) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 int cvmx_mdio_read (int,int,int) ; 
 TYPE_3__ cvmx_override_board_link_get (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 TYPE_4__* cvmx_sysinfo_get () ; 

cvmx_helper_link_info_t __cvmx_helper_board_link_get(int ipd_port)
{
	cvmx_helper_link_info_t result;
	int phy_addr;
	int is_broadcom_phy = 0;

	/* Give the user a chance to override the processing of this function */
	if (cvmx_override_board_link_get)
		return cvmx_override_board_link_get(ipd_port);

	/* Unless we fix it later, all links are defaulted to down */
	result.u64 = 0;

	/*
	 * This switch statement should handle all ports that either don't use
	 * Marvell PHYS, or don't support in-band status.
	 */
	switch (cvmx_sysinfo_get()->board_type) {
	case CVMX_BOARD_TYPE_SIM:
		/* The simulator gives you a simulated 1Gbps full duplex link */
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 1000;
		return result;
	case CVMX_BOARD_TYPE_EBH3100:
	case CVMX_BOARD_TYPE_CN3010_EVB_HS5:
	case CVMX_BOARD_TYPE_CN3005_EVB_HS5:
	case CVMX_BOARD_TYPE_CN3020_EVB_HS5:
		/* Port 1 on these boards is always Gigabit */
		if (ipd_port == 1) {
			result.s.link_up = 1;
			result.s.full_duplex = 1;
			result.s.speed = 1000;
			return result;
		}
		/* Fall through to the generic code below */
		break;
	case CVMX_BOARD_TYPE_CUST_NB5:
		/* Port 1 on these boards is always Gigabit */
		if (ipd_port == 1) {
			result.s.link_up = 1;
			result.s.full_duplex = 1;
			result.s.speed = 1000;
			return result;
		} else		/* The other port uses a broadcom PHY */
			is_broadcom_phy = 1;
		break;
	case CVMX_BOARD_TYPE_BBGW_REF:
		/* Port 1 on these boards is always Gigabit */
		if (ipd_port == 2) {
			/* Port 2 is not hooked up */
			result.u64 = 0;
			return result;
		} else {
			/* Ports 0 and 1 connect to the switch */
			result.s.link_up = 1;
			result.s.full_duplex = 1;
			result.s.speed = 1000;
			return result;
		}
		break;
	}

	phy_addr = cvmx_helper_board_get_mii_address(ipd_port);
	if (phy_addr != -1) {
		if (is_broadcom_phy) {
			/*
			 * Below we are going to read SMI/MDIO
			 * register 0x19 which works on Broadcom
			 * parts
			 */
			int phy_status =
			    cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff,
					   0x19);
			switch ((phy_status >> 8) & 0x7) {
			case 0:
				result.u64 = 0;
				break;
			case 1:
				result.s.link_up = 1;
				result.s.full_duplex = 0;
				result.s.speed = 10;
				break;
			case 2:
				result.s.link_up = 1;
				result.s.full_duplex = 1;
				result.s.speed = 10;
				break;
			case 3:
				result.s.link_up = 1;
				result.s.full_duplex = 0;
				result.s.speed = 100;
				break;
			case 4:
				result.s.link_up = 1;
				result.s.full_duplex = 1;
				result.s.speed = 100;
				break;
			case 5:
				result.s.link_up = 1;
				result.s.full_duplex = 1;
				result.s.speed = 100;
				break;
			case 6:
				result.s.link_up = 1;
				result.s.full_duplex = 0;
				result.s.speed = 1000;
				break;
			case 7:
				result.s.link_up = 1;
				result.s.full_duplex = 1;
				result.s.speed = 1000;
				break;
			}
		} else {
			/*
			 * This code assumes we are using a Marvell
			 * Gigabit PHY. All the speed information can
			 * be read from register 17 in one
			 * go. Somebody using a different PHY will
			 * need to handle it above in the board
			 * specific area.
			 */
			int phy_status =
			    cvmx_mdio_read(phy_addr >> 8, phy_addr & 0xff, 17);

			/*
			 * If the resolve bit 11 isn't set, see if
			 * autoneg is turned off (bit 12, reg 0). The
			 * resolve bit doesn't get set properly when
			 * autoneg is off, so force it.
			 */
			if ((phy_status & (1 << 11)) == 0) {
				int auto_status =
				    cvmx_mdio_read(phy_addr >> 8,
						   phy_addr & 0xff, 0);
				if ((auto_status & (1 << 12)) == 0)
					phy_status |= 1 << 11;
			}

			/*
			 * Only return a link if the PHY has finished
			 * auto negotiation and set the resolved bit
			 * (bit 11)
			 */
			if (phy_status & (1 << 11)) {
				result.s.link_up = 1;
				result.s.full_duplex = ((phy_status >> 13) & 1);
				switch ((phy_status >> 14) & 3) {
				case 0:	/* 10 Mbps */
					result.s.speed = 10;
					break;
				case 1:	/* 100 Mbps */
					result.s.speed = 100;
					break;
				case 2:	/* 1 Gbps */
					result.s.speed = 1000;
					break;
				case 3:	/* Illegal */
					result.u64 = 0;
					break;
				}
			}
		}
	} else if (OCTEON_IS_MODEL(OCTEON_CN3XXX)
		   || OCTEON_IS_MODEL(OCTEON_CN58XX)
		   || OCTEON_IS_MODEL(OCTEON_CN50XX)) {
		/*
		 * We don't have a PHY address, so attempt to use
		 * in-band status. It is really important that boards
		 * not supporting in-band status never get
		 * here. Reading broken in-band status tends to do bad
		 * things
		 */
		union cvmx_gmxx_rxx_rx_inbnd inband_status;
		int interface = cvmx_helper_get_interface_num(ipd_port);
		int index = cvmx_helper_get_interface_index_num(ipd_port);
		inband_status.u64 =
		    cvmx_read_csr(CVMX_GMXX_RXX_RX_INBND(index, interface));

		result.s.link_up = inband_status.s.status;
		result.s.full_duplex = inband_status.s.duplex;
		switch (inband_status.s.speed) {
		case 0:	/* 10 Mbps */
			result.s.speed = 10;
			break;
		case 1:	/* 100 Mbps */
			result.s.speed = 100;
			break;
		case 2:	/* 1 Gbps */
			result.s.speed = 1000;
			break;
		case 3:	/* Illegal */
			result.u64 = 0;
			break;
		}
	} else {
		/*
		 * We don't have a PHY address and we don't have
		 * in-band status. There is no way to determine the
		 * link speed. Return down assuming this port isn't
		 * wired
		 */
		result.u64 = 0;
	}

	/* If link is down, return all fields as zero. */
	if (!result.s.link_up)
		result.u64 = 0;

	return result;
}