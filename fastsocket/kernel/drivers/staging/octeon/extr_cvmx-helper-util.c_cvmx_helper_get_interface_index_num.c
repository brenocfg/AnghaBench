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
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 

int cvmx_helper_get_interface_index_num(int ipd_port)
{
	if (ipd_port < 32)
		return ipd_port & 15;
	else if (ipd_port < 36)
		return ipd_port & 3;
	else if (ipd_port < 40)
		return ipd_port & 3;
	else
		cvmx_dprintf("cvmx_helper_get_interface_index_num: "
			     "Illegal IPD port number\n");

	return -1;
}