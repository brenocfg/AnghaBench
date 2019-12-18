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
 int /*<<< orphan*/  CVMX_ASXX_TX_HI_WATERX (int,int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __cvmx_helper_errata_asx_pass1(int interface, int port,
					  int cpu_clock_hz)
{
	/* Set hi water mark as per errata GMX-4 */
	if (cpu_clock_hz >= 325000000 && cpu_clock_hz < 375000000)
		cvmx_write_csr(CVMX_ASXX_TX_HI_WATERX(port, interface), 12);
	else if (cpu_clock_hz >= 375000000 && cpu_clock_hz < 437000000)
		cvmx_write_csr(CVMX_ASXX_TX_HI_WATERX(port, interface), 11);
	else if (cpu_clock_hz >= 437000000 && cpu_clock_hz < 550000000)
		cvmx_write_csr(CVMX_ASXX_TX_HI_WATERX(port, interface), 10);
	else if (cpu_clock_hz >= 550000000 && cpu_clock_hz < 687000000)
		cvmx_write_csr(CVMX_ASXX_TX_HI_WATERX(port, interface), 9);
	else
		cvmx_dprintf("Illegal clock frequency (%d). "
			"CVMX_ASXX_TX_HI_WATERX not set\n", cpu_clock_hz);
	return 0;
}