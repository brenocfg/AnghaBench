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
struct TYPE_2__ {int duplex; int slottime; int speed; int en; } ;
union cvmx_gmxx_prtx_cfg {int u64; TYPE_1__ s; } ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ASXX_PRT_LOOP (int) ; 
 int /*<<< orphan*/  CVMX_ASXX_RX_PRT_EN (int) ; 
 int /*<<< orphan*/  CVMX_ASXX_TX_PRT_EN (int) ; 
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TXX_BURST (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TXX_CLK (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TXX_SLOT (int,int) ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

void cvmx_helper_rgmii_internal_loopback(int port)
{
	int interface = (port >> 4) & 1;
	int index = port & 0xf;
	uint64_t tmp;

	union cvmx_gmxx_prtx_cfg gmx_cfg;
	gmx_cfg.u64 = 0;
	gmx_cfg.s.duplex = 1;
	gmx_cfg.s.slottime = 1;
	gmx_cfg.s.speed = 1;
	cvmx_write_csr(CVMX_GMXX_TXX_CLK(index, interface), 1);
	cvmx_write_csr(CVMX_GMXX_TXX_SLOT(index, interface), 0x200);
	cvmx_write_csr(CVMX_GMXX_TXX_BURST(index, interface), 0x2000);
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);
	tmp = cvmx_read_csr(CVMX_ASXX_PRT_LOOP(interface));
	cvmx_write_csr(CVMX_ASXX_PRT_LOOP(interface), (1 << index) | tmp);
	tmp = cvmx_read_csr(CVMX_ASXX_TX_PRT_EN(interface));
	cvmx_write_csr(CVMX_ASXX_TX_PRT_EN(interface), (1 << index) | tmp);
	tmp = cvmx_read_csr(CVMX_ASXX_RX_PRT_EN(interface));
	cvmx_write_csr(CVMX_ASXX_RX_PRT_EN(interface), (1 << index) | tmp);
	gmx_cfg.s.en = 1;
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);
}