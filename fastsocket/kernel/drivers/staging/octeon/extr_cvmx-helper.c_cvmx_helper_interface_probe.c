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
#define  CVMX_HELPER_INTERFACE_MODE_DISABLED 137 
#define  CVMX_HELPER_INTERFACE_MODE_GMII 136 
#define  CVMX_HELPER_INTERFACE_MODE_LOOP 135 
#define  CVMX_HELPER_INTERFACE_MODE_NPI 134 
#define  CVMX_HELPER_INTERFACE_MODE_PCIE 133 
#define  CVMX_HELPER_INTERFACE_MODE_PICMG 132 
#define  CVMX_HELPER_INTERFACE_MODE_RGMII 131 
#define  CVMX_HELPER_INTERFACE_MODE_SGMII 130 
#define  CVMX_HELPER_INTERFACE_MODE_SPI 129 
#define  CVMX_HELPER_INTERFACE_MODE_XAUI 128 
 int /*<<< orphan*/  CVMX_SYNCWS ; 
 int /*<<< orphan*/  __cvmx_helper_board_interface_probe (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_helper_loop_probe (int) ; 
 int /*<<< orphan*/  __cvmx_helper_npi_probe (int) ; 
 int /*<<< orphan*/  __cvmx_helper_rgmii_probe (int) ; 
 int /*<<< orphan*/  __cvmx_helper_sgmii_probe (int) ; 
 int /*<<< orphan*/  __cvmx_helper_spi_probe (int) ; 
 int /*<<< orphan*/  __cvmx_helper_xaui_probe (int) ; 
 int cvmx_helper_interface_get_mode (int) ; 
 int /*<<< orphan*/ * interface_port_count ; 

int cvmx_helper_interface_probe(int interface)
{
	/* At this stage in the game we don't want packets to be moving yet.
	   The following probe calls should perform hardware setup
	   needed to determine port counts. Receive must still be disabled */
	switch (cvmx_helper_interface_get_mode(interface)) {
		/* These types don't support ports to IPD/PKO */
	case CVMX_HELPER_INTERFACE_MODE_DISABLED:
	case CVMX_HELPER_INTERFACE_MODE_PCIE:
		interface_port_count[interface] = 0;
		break;
		/* XAUI is a single high speed port */
	case CVMX_HELPER_INTERFACE_MODE_XAUI:
		interface_port_count[interface] =
		    __cvmx_helper_xaui_probe(interface);
		break;
		/*
		 * RGMII/GMII/MII are all treated about the same. Most
		 * functions refer to these ports as RGMII.
		 */
	case CVMX_HELPER_INTERFACE_MODE_RGMII:
	case CVMX_HELPER_INTERFACE_MODE_GMII:
		interface_port_count[interface] =
		    __cvmx_helper_rgmii_probe(interface);
		break;
		/*
		 * SPI4 can have 1-16 ports depending on the device at
		 * the other end.
		 */
	case CVMX_HELPER_INTERFACE_MODE_SPI:
		interface_port_count[interface] =
		    __cvmx_helper_spi_probe(interface);
		break;
		/*
		 * SGMII can have 1-4 ports depending on how many are
		 * hooked up.
		 */
	case CVMX_HELPER_INTERFACE_MODE_SGMII:
	case CVMX_HELPER_INTERFACE_MODE_PICMG:
		interface_port_count[interface] =
		    __cvmx_helper_sgmii_probe(interface);
		break;
		/* PCI target Network Packet Interface */
	case CVMX_HELPER_INTERFACE_MODE_NPI:
		interface_port_count[interface] =
		    __cvmx_helper_npi_probe(interface);
		break;
		/*
		 * Special loopback only ports. These are not the same
		 * as other ports in loopback mode.
		 */
	case CVMX_HELPER_INTERFACE_MODE_LOOP:
		interface_port_count[interface] =
		    __cvmx_helper_loop_probe(interface);
		break;
	}

	interface_port_count[interface] =
	    __cvmx_helper_board_interface_probe(interface,
						interface_port_count
						[interface]);

	/* Make sure all global variables propagate to other cores */
	CVMX_SYNCWS;

	return 0;
}