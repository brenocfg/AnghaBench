#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int mode0; int mode1; } ;
union cvmx_pko_reg_gmx_port_mode {void* u64; TYPE_3__ s; } ;
struct TYPE_8__ {int cnt; } ;
union cvmx_gmxx_txx_thresh {void* u64; TYPE_4__ s; } ;
struct TYPE_5__ {int prts; } ;
union cvmx_gmxx_tx_prts {void* u64; TYPE_1__ s; } ;
struct TYPE_6__ {int prts; } ;
union cvmx_gmxx_rx_prts {void* u64; TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RX_PRTS (int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TXX_THRESH (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TX_PRTS (int) ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_GMII ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_RGMII ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_SGMII ; 
 scalar_t__ CVMX_HELPER_INTERFACE_MODE_XAUI ; 
 int /*<<< orphan*/  CVMX_PKO_REG_GMX_PORT_MODE ; 
 int /*<<< orphan*/  OCTEON_CN30XX ; 
 int /*<<< orphan*/  OCTEON_CN31XX ; 
 int /*<<< orphan*/  OCTEON_CN50XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 scalar_t__ cvmx_helper_interface_get_mode (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

int __cvmx_helper_setup_gmx(int interface, int num_ports)
{
	union cvmx_gmxx_tx_prts gmx_tx_prts;
	union cvmx_gmxx_rx_prts gmx_rx_prts;
	union cvmx_pko_reg_gmx_port_mode pko_mode;
	union cvmx_gmxx_txx_thresh gmx_tx_thresh;
	int index;

	/* Tell GMX the number of TX ports on this interface */
	gmx_tx_prts.u64 = cvmx_read_csr(CVMX_GMXX_TX_PRTS(interface));
	gmx_tx_prts.s.prts = num_ports;
	cvmx_write_csr(CVMX_GMXX_TX_PRTS(interface), gmx_tx_prts.u64);

	/* Tell GMX the number of RX ports on this interface.  This only
	 ** applies to *GMII and XAUI ports */
	if (cvmx_helper_interface_get_mode(interface) ==
	    CVMX_HELPER_INTERFACE_MODE_RGMII
	    || cvmx_helper_interface_get_mode(interface) ==
	    CVMX_HELPER_INTERFACE_MODE_SGMII
	    || cvmx_helper_interface_get_mode(interface) ==
	    CVMX_HELPER_INTERFACE_MODE_GMII
	    || cvmx_helper_interface_get_mode(interface) ==
	    CVMX_HELPER_INTERFACE_MODE_XAUI) {
		if (num_ports > 4) {
			cvmx_dprintf("__cvmx_helper_setup_gmx: Illegal "
				     "num_ports\n");
			return -1;
		}

		gmx_rx_prts.u64 = cvmx_read_csr(CVMX_GMXX_RX_PRTS(interface));
		gmx_rx_prts.s.prts = num_ports;
		cvmx_write_csr(CVMX_GMXX_RX_PRTS(interface), gmx_rx_prts.u64);
	}

	/* Skip setting CVMX_PKO_REG_GMX_PORT_MODE on 30XX, 31XX, and 50XX */
	if (!OCTEON_IS_MODEL(OCTEON_CN30XX) && !OCTEON_IS_MODEL(OCTEON_CN31XX)
	    && !OCTEON_IS_MODEL(OCTEON_CN50XX)) {
		/* Tell PKO the number of ports on this interface */
		pko_mode.u64 = cvmx_read_csr(CVMX_PKO_REG_GMX_PORT_MODE);
		if (interface == 0) {
			if (num_ports == 1)
				pko_mode.s.mode0 = 4;
			else if (num_ports == 2)
				pko_mode.s.mode0 = 3;
			else if (num_ports <= 4)
				pko_mode.s.mode0 = 2;
			else if (num_ports <= 8)
				pko_mode.s.mode0 = 1;
			else
				pko_mode.s.mode0 = 0;
		} else {
			if (num_ports == 1)
				pko_mode.s.mode1 = 4;
			else if (num_ports == 2)
				pko_mode.s.mode1 = 3;
			else if (num_ports <= 4)
				pko_mode.s.mode1 = 2;
			else if (num_ports <= 8)
				pko_mode.s.mode1 = 1;
			else
				pko_mode.s.mode1 = 0;
		}
		cvmx_write_csr(CVMX_PKO_REG_GMX_PORT_MODE, pko_mode.u64);
	}

	/*
	 * Set GMX to buffer as much data as possible before starting
	 * transmit.  This reduces the chances that we have a TX under
	 * run due to memory contention. Any packet that fits entirely
	 * in the GMX FIFO can never have an under run regardless of
	 * memory load.
	 */
	gmx_tx_thresh.u64 = cvmx_read_csr(CVMX_GMXX_TXX_THRESH(0, interface));
	if (OCTEON_IS_MODEL(OCTEON_CN30XX) || OCTEON_IS_MODEL(OCTEON_CN31XX)
	    || OCTEON_IS_MODEL(OCTEON_CN50XX)) {
		/* These chips have a fixed max threshold of 0x40 */
		gmx_tx_thresh.s.cnt = 0x40;
	} else {
		/* Choose the max value for the number of ports */
		if (num_ports <= 1)
			gmx_tx_thresh.s.cnt = 0x100 / 1;
		else if (num_ports == 2)
			gmx_tx_thresh.s.cnt = 0x100 / 2;
		else
			gmx_tx_thresh.s.cnt = 0x100 / 4;
	}
	/*
	 * SPI and XAUI can have lots of ports but the GMX hardware
	 * only ever has a max of 4.
	 */
	if (num_ports > 4)
		num_ports = 4;
	for (index = 0; index < num_ports; index++)
		cvmx_write_csr(CVMX_GMXX_TXX_THRESH(index, interface),
			       gmx_tx_thresh.u64);

	return 0;
}