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
typedef  unsigned int u32 ;
struct TYPE_3__ {unsigned int start; scalar_t__ size; } ;
struct TYPE_4__ {TYPE_1__ ocq; } ;
struct adapter {TYPE_2__ vres; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 unsigned int BIR (int) ; 
 unsigned int MEMWIN0_APERTURE ; 
 unsigned int MEMWIN0_BASE ; 
 unsigned int MEMWIN1_APERTURE ; 
 unsigned int MEMWIN1_BASE ; 
 unsigned int MEMWIN2_APERTURE ; 
 unsigned int MEMWIN2_BASE ; 
 unsigned int OCQ_WIN_OFFSET (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_BASE_WIN ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_OFFSET ; 
 int /*<<< orphan*/  PCIE_MEM_ACCESS_REG (int /*<<< orphan*/ ,int) ; 
 unsigned int WINDOW (scalar_t__) ; 
 scalar_t__ ilog2 (unsigned int) ; 
 unsigned int pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int roundup_pow_of_two (scalar_t__) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void setup_memwin(struct adapter *adap)
{
	u32 bar0;

	bar0 = pci_resource_start(adap->pdev, 0);  /* truncation intentional */
	t4_write_reg(adap, PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN, 0),
		     (bar0 + MEMWIN0_BASE) | BIR(0) |
		     WINDOW(ilog2(MEMWIN0_APERTURE) - 10));
	t4_write_reg(adap, PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN, 1),
		     (bar0 + MEMWIN1_BASE) | BIR(0) |
		     WINDOW(ilog2(MEMWIN1_APERTURE) - 10));
	t4_write_reg(adap, PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN, 2),
		     (bar0 + MEMWIN2_BASE) | BIR(0) |
		     WINDOW(ilog2(MEMWIN2_APERTURE) - 10));
	if (adap->vres.ocq.size) {
		unsigned int start, sz_kb;

		start = pci_resource_start(adap->pdev, 2) +
			OCQ_WIN_OFFSET(adap->pdev, &adap->vres);
		sz_kb = roundup_pow_of_two(adap->vres.ocq.size) >> 10;
		t4_write_reg(adap,
			     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_BASE_WIN, 3),
			     start | BIR(1) | WINDOW(ilog2(sz_kb)));
		t4_write_reg(adap,
			     PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET, 3),
			     adap->vres.ocq.start);
		t4_read_reg(adap,
			    PCIE_MEM_ACCESS_REG(PCIE_MEM_ACCESS_OFFSET, 3));
	}
}