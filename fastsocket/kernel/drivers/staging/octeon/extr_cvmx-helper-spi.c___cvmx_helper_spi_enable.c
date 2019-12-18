#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int crc_en; } ;
union cvmx_pip_prt_cfgx {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct TYPE_4__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int /*<<< orphan*/  CVMX_HELPER_SPI_TIMEOUT ; 
 int /*<<< orphan*/  CVMX_PIP_PRT_CFGX (int) ; 
 int /*<<< orphan*/  CVMX_SPI_MODE_DUPLEX ; 
 int /*<<< orphan*/  __cvmx_interrupt_gmxx_enable (int) ; 
 int /*<<< orphan*/  __cvmx_interrupt_spxx_int_msk_enable (int) ; 
 int /*<<< orphan*/  __cvmx_interrupt_stxx_int_msk_enable (int) ; 
 int cvmx_helper_ports_on_interface (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_spi4000_initialize (int) ; 
 scalar_t__ cvmx_spi4000_is_present (int) ; 
 int /*<<< orphan*/  cvmx_spi_start_interface (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __cvmx_helper_spi_enable(int interface)
{
	/*
	 * Normally the ethernet L2 CRC is checked and stripped in the
	 * GMX block.  When you are using SPI, this isn' the case and
	 * IPD needs to check the L2 CRC.
	 */
	int num_ports = cvmx_helper_ports_on_interface(interface);
	int ipd_port;
	for (ipd_port = interface * 16; ipd_port < interface * 16 + num_ports;
	     ipd_port++) {
		union cvmx_pip_prt_cfgx port_config;
		port_config.u64 = cvmx_read_csr(CVMX_PIP_PRT_CFGX(ipd_port));
		port_config.s.crc_en = 1;
		cvmx_write_csr(CVMX_PIP_PRT_CFGX(ipd_port), port_config.u64);
	}

	if (cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) {
		cvmx_spi_start_interface(interface, CVMX_SPI_MODE_DUPLEX,
					 CVMX_HELPER_SPI_TIMEOUT, num_ports);
		if (cvmx_spi4000_is_present(interface))
			cvmx_spi4000_initialize(interface);
	}
	__cvmx_interrupt_spxx_int_msk_enable(interface);
	__cvmx_interrupt_stxx_int_msk_enable(interface);
	__cvmx_interrupt_gmxx_enable(interface);
	return 0;
}