#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dat; scalar_t__ pending; } ;
union cvmx_smix_wr_dat {void* u64; TYPE_1__ s; } ;
struct TYPE_6__ {int dat; scalar_t__ val; scalar_t__ pending; } ;
union cvmx_smix_rd_dat {TYPE_3__ s; void* u64; } ;
struct TYPE_5__ {int phy_adr; int reg_adr; int /*<<< orphan*/  phy_op; } ;
union cvmx_smix_cmd {void* u64; TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SMIX_CMD (int) ; 
 int /*<<< orphan*/  CVMX_SMIX_RD_DAT (int) ; 
 int /*<<< orphan*/  CVMX_SMIX_WR_DAT (int) ; 
 int /*<<< orphan*/  MDIO_CLAUSE_45_ADDRESS ; 
 int /*<<< orphan*/  MDIO_CLAUSE_45_READ ; 
 int /*<<< orphan*/  OCTEON_FEATURE_MDIO_CLAUSE_45 ; 
 int /*<<< orphan*/  __cvmx_mdio_set_clause45_mode (int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,int,int,int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_wait (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  octeon_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cvmx_mdio_45_read(int bus_id, int phy_id, int device,
				    int location)
{
	union cvmx_smix_cmd smi_cmd;
	union cvmx_smix_rd_dat smi_rd;
	union cvmx_smix_wr_dat smi_wr;
	int timeout = 1000;

	if (!octeon_has_feature(OCTEON_FEATURE_MDIO_CLAUSE_45))
		return -1;

	__cvmx_mdio_set_clause45_mode(bus_id);

	smi_wr.u64 = 0;
	smi_wr.s.dat = location;
	cvmx_write_csr(CVMX_SMIX_WR_DAT(bus_id), smi_wr.u64);

	smi_cmd.u64 = 0;
	smi_cmd.s.phy_op = MDIO_CLAUSE_45_ADDRESS;
	smi_cmd.s.phy_adr = phy_id;
	smi_cmd.s.reg_adr = device;
	cvmx_write_csr(CVMX_SMIX_CMD(bus_id), smi_cmd.u64);

	do {
		cvmx_wait(1000);
		smi_wr.u64 = cvmx_read_csr(CVMX_SMIX_WR_DAT(bus_id));
	} while (smi_wr.s.pending && --timeout);
	if (timeout <= 0) {
		cvmx_dprintf("cvmx_mdio_45_read: bus_id %d phy_id %2d "
			     "device %2d register %2d   TIME OUT(address)\n",
		     bus_id, phy_id, device, location);
		return -1;
	}

	smi_cmd.u64 = 0;
	smi_cmd.s.phy_op = MDIO_CLAUSE_45_READ;
	smi_cmd.s.phy_adr = phy_id;
	smi_cmd.s.reg_adr = device;
	cvmx_write_csr(CVMX_SMIX_CMD(bus_id), smi_cmd.u64);

	do {
		cvmx_wait(1000);
		smi_rd.u64 = cvmx_read_csr(CVMX_SMIX_RD_DAT(bus_id));
	} while (smi_rd.s.pending && --timeout);

	if (timeout <= 0) {
		cvmx_dprintf("cvmx_mdio_45_read: bus_id %d phy_id %2d "
			     "device %2d register %2d   TIME OUT(data)\n",
		     bus_id, phy_id, device, location);
		return -1;
	}

	if (smi_rd.s.val)
		return smi_rd.s.dat;
	else {
		cvmx_dprintf("cvmx_mdio_45_read: bus_id %d phy_id %2d "
			     "device %2d register %2d   INVALID READ\n",
		     bus_id, phy_id, device, location);
		return -1;
	}
}