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
typedef  int cvmx_helper_interface_mode_t ;

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

const char *cvmx_helper_interface_mode_to_string(cvmx_helper_interface_mode_t
						 mode)
{
	switch (mode) {
	case CVMX_HELPER_INTERFACE_MODE_DISABLED:
		return "DISABLED";
	case CVMX_HELPER_INTERFACE_MODE_RGMII:
		return "RGMII";
	case CVMX_HELPER_INTERFACE_MODE_GMII:
		return "GMII";
	case CVMX_HELPER_INTERFACE_MODE_SPI:
		return "SPI";
	case CVMX_HELPER_INTERFACE_MODE_PCIE:
		return "PCIE";
	case CVMX_HELPER_INTERFACE_MODE_XAUI:
		return "XAUI";
	case CVMX_HELPER_INTERFACE_MODE_SGMII:
		return "SGMII";
	case CVMX_HELPER_INTERFACE_MODE_PICMG:
		return "PICMG";
	case CVMX_HELPER_INTERFACE_MODE_NPI:
		return "NPI";
	case CVMX_HELPER_INTERFACE_MODE_LOOP:
		return "LOOP";
	}
	return "UNKNOWN";
}