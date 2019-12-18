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
struct TYPE_2__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int /*<<< orphan*/  OCTEON_CN30XX_PASS1 ; 
 int /*<<< orphan*/  OCTEON_CN31XX_PASS1 ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_helper_errata_fix_ipd_ptr_alignment () ; 
 int /*<<< orphan*/  __cvmx_helper_packet_hardware_enable (int) ; 
 int cvmx_helper_get_number_of_interfaces () ; 
 scalar_t__ cvmx_helper_ports_on_interface (int) ; 
 int /*<<< orphan*/  cvmx_ipd_enable () ; 
 int /*<<< orphan*/  cvmx_pko_enable () ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

int cvmx_helper_ipd_and_packet_input_enable(void)
{
	int num_interfaces;
	int interface;

	/* Enable IPD */
	cvmx_ipd_enable();

	/*
	 * Time to enable hardware ports packet input and output. Note
	 * that at this point IPD/PIP must be fully functional and PKO
	 * must be disabled
	 */
	num_interfaces = cvmx_helper_get_number_of_interfaces();
	for (interface = 0; interface < num_interfaces; interface++) {
		if (cvmx_helper_ports_on_interface(interface) > 0)
			__cvmx_helper_packet_hardware_enable(interface);
	}

	/* Finally enable PKO now that the entire path is up and running */
	cvmx_pko_enable();

	if ((OCTEON_IS_MODEL(OCTEON_CN31XX_PASS1)
	     || OCTEON_IS_MODEL(OCTEON_CN30XX_PASS1))
	    && (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM))
		__cvmx_helper_errata_fix_ipd_ptr_alignment();
	return 0;
}