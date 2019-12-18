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
 int /*<<< orphan*/  __cvmx_helper_port_setup_ipd (int) ; 
 int cvmx_helper_get_ipd_port (int,int /*<<< orphan*/ ) ; 
 int* interface_port_count ; 

__attribute__((used)) static int __cvmx_helper_interface_setup_ipd(int interface)
{
	int ipd_port = cvmx_helper_get_ipd_port(interface, 0);
	int num_ports = interface_port_count[interface];

	while (num_ports--) {
		__cvmx_helper_port_setup_ipd(ipd_port);
		ipd_port++;
	}
	return 0;
}