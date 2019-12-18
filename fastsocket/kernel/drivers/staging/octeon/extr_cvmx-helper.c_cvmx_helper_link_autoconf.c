#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ u64; } ;
typedef  TYPE_1__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 TYPE_1__ cvmx_helper_link_get (int) ; 
 int /*<<< orphan*/  cvmx_helper_link_set (int,TYPE_1__) ; 
 int cvmx_helper_ports_on_interface (int) ; 
 TYPE_1__* port_link_info ; 

cvmx_helper_link_info_t cvmx_helper_link_autoconf(int ipd_port)
{
	cvmx_helper_link_info_t link_info;
	int interface = cvmx_helper_get_interface_num(ipd_port);
	int index = cvmx_helper_get_interface_index_num(ipd_port);

	if (index >= cvmx_helper_ports_on_interface(interface)) {
		link_info.u64 = 0;
		return link_info;
	}

	link_info = cvmx_helper_link_get(ipd_port);
	if (link_info.u64 == port_link_info[ipd_port].u64)
		return link_info;

	/* If we fail to set the link speed, port_link_info will not change */
	cvmx_helper_link_set(ipd_port, link_info);

	/*
	 * port_link_info should be the current value, which will be
	 * different than expect if cvmx_helper_link_set() failed.
	 */
	return port_link_info[ipd_port];
}