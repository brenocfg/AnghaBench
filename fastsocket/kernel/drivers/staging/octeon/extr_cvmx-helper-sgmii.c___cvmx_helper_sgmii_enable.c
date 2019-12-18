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
struct TYPE_2__ {int en; } ;
union cvmx_gmxx_prtx_cfg {int /*<<< orphan*/  u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  __cvmx_helper_sgmii_hardware_init (int,int) ; 
 int /*<<< orphan*/  __cvmx_interrupt_gmxx_enable (int) ; 
 int /*<<< orphan*/  __cvmx_interrupt_pcsx_intx_en_reg_enable (int,int) ; 
 int /*<<< orphan*/  __cvmx_interrupt_pcsxx_int_en_reg_enable (int) ; 
 int cvmx_helper_ports_on_interface (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __cvmx_helper_sgmii_enable(int interface)
{
	int num_ports = cvmx_helper_ports_on_interface(interface);
	int index;

	__cvmx_helper_sgmii_hardware_init(interface, num_ports);

	for (index = 0; index < num_ports; index++) {
		union cvmx_gmxx_prtx_cfg gmxx_prtx_cfg;
		gmxx_prtx_cfg.u64 =
		    cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
		gmxx_prtx_cfg.s.en = 1;
		cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface),
			       gmxx_prtx_cfg.u64);
		__cvmx_interrupt_pcsx_intx_en_reg_enable(index, interface);
	}
	__cvmx_interrupt_pcsxx_int_en_reg_enable(interface);
	__cvmx_interrupt_gmxx_enable(interface);
	return 0;
}