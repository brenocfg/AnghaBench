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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
union cvmx_pescx_cfg_rd {TYPE_1__ s; scalar_t__ u64; } ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PESCX_CFG_RD (int) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint32_t cvmx_pcie_cfgx_read(int pcie_port, uint32_t cfg_offset)
{
	union cvmx_pescx_cfg_rd pescx_cfg_rd;
	pescx_cfg_rd.u64 = 0;
	pescx_cfg_rd.s.addr = cfg_offset;
	cvmx_write_csr(CVMX_PESCX_CFG_RD(pcie_port), pescx_cfg_rd.u64);
	pescx_cfg_rd.u64 = cvmx_read_csr(CVMX_PESCX_CFG_RD(pcie_port));
	return pescx_cfg_rd.s.data;
}