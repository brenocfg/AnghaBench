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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPI_TEST_FUNC_PRB_CTL ; 
 int /*<<< orphan*/  MPI_TEST_FUNC_PRB_EN ; 
 int /*<<< orphan*/  PRB_MX_ADDR_FC_CLOCK ; 
 int /*<<< orphan*/  PRB_MX_ADDR_PCI_CLOCK ; 
 int /*<<< orphan*/  PRB_MX_ADDR_SYS_CLOCK ; 
 int /*<<< orphan*/  PRB_MX_ADDR_VALID_FC_MOD ; 
 int /*<<< orphan*/  PRB_MX_ADDR_VALID_PCI_MOD ; 
 int /*<<< orphan*/  PRB_MX_ADDR_VALID_SYS_MOD ; 
 int /*<<< orphan*/  PRB_MX_ADDR_VALID_XGM_MOD ; 
 int /*<<< orphan*/  PRB_MX_ADDR_XGM_CLOCK ; 
 unsigned int* ql_get_probe (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  ql_write_mpi_reg (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_get_probe_dump(struct ql_adapter *qdev, unsigned int *buf)
{
	/* First we have to enable the probe mux */
	ql_write_mpi_reg(qdev, MPI_TEST_FUNC_PRB_CTL, MPI_TEST_FUNC_PRB_EN);
	buf = ql_get_probe(qdev, PRB_MX_ADDR_SYS_CLOCK,
			PRB_MX_ADDR_VALID_SYS_MOD, buf);
	buf = ql_get_probe(qdev, PRB_MX_ADDR_PCI_CLOCK,
			PRB_MX_ADDR_VALID_PCI_MOD, buf);
	buf = ql_get_probe(qdev, PRB_MX_ADDR_XGM_CLOCK,
			PRB_MX_ADDR_VALID_XGM_MOD, buf);
	buf = ql_get_probe(qdev, PRB_MX_ADDR_FC_CLOCK,
			PRB_MX_ADDR_VALID_FC_MOD, buf);
	return 0;

}