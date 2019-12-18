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
struct TYPE_4__ {int dat; scalar_t__ pending; } ;
union cvmx_smix_wr_dat {scalar_t__ u64; TYPE_2__ s; } ;
struct TYPE_3__ {int phy_adr; int reg_adr; int /*<<< orphan*/  phy_op; } ;
union cvmx_smix_cmd {scalar_t__ u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SMIX_CMD (int) ; 
 int /*<<< orphan*/  CVMX_SMIX_WR_DAT (int) ; 
 int /*<<< orphan*/  MDIO_CLAUSE_22_WRITE ; 
 int /*<<< orphan*/  OCTEON_FEATURE_MDIO_CLAUSE_45 ; 
 int /*<<< orphan*/  __cvmx_mdio_set_clause22_mode (int) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvmx_mdio_write(int bus_id, int phy_id, int location, int val)
{
	union cvmx_smix_cmd smi_cmd;
	union cvmx_smix_wr_dat smi_wr;
	int timeout = 1000;

	if (octeon_has_feature(OCTEON_FEATURE_MDIO_CLAUSE_45))
		__cvmx_mdio_set_clause22_mode(bus_id);

	smi_wr.u64 = 0;
	smi_wr.s.dat = val;
	cvmx_write_csr(CVMX_SMIX_WR_DAT(bus_id), smi_wr.u64);

	smi_cmd.u64 = 0;
	smi_cmd.s.phy_op = MDIO_CLAUSE_22_WRITE;
	smi_cmd.s.phy_adr = phy_id;
	smi_cmd.s.reg_adr = location;
	cvmx_write_csr(CVMX_SMIX_CMD(bus_id), smi_cmd.u64);

	do {
		cvmx_wait(1000);
		smi_wr.u64 = cvmx_read_csr(CVMX_SMIX_WR_DAT(bus_id));
	} while (smi_wr.s.pending && --timeout);
	if (timeout <= 0)
		return -1;

	return 0;
}