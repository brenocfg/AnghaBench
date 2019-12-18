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
#define  CVMX_BOARD_TYPE_BBGW_REF 131 
#define  CVMX_BOARD_TYPE_CN3005_EVB_HS5 130 
#define  CVMX_BOARD_TYPE_EBH5600 129 
#define  CVMX_BOARD_TYPE_NIC_XLE_4G 128 
 TYPE_1__* cvmx_sysinfo_get () ; 

int __cvmx_helper_board_interface_probe(int interface, int supported_ports)
{
	switch (cvmx_sysinfo_get()->board_type) {
	case CVMX_BOARD_TYPE_CN3005_EVB_HS5:
		if (interface == 0)
			return 2;
		break;
	case CVMX_BOARD_TYPE_BBGW_REF:
		if (interface == 0)
			return 2;
		break;
	case CVMX_BOARD_TYPE_NIC_XLE_4G:
		if (interface == 0)
			return 0;
		break;
		/* The 2nd interface on the EBH5600 is connected to the Marvel switch,
		   which we don't support. Disable ports connected to it */
	case CVMX_BOARD_TYPE_EBH5600:
		if (interface == 1)
			return 0;
		break;
	}
	return supported_ports;
}