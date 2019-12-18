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
typedef  int u32 ;
struct ql_adapter {int /*<<< orphan*/  ndev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MB_SET_MPI_TFK_RESUME ; 
 int /*<<< orphan*/  MB_SET_MPI_TFK_STOP ; 
 int /*<<< orphan*/  QL_ASIC_RECOVERY ; 
 int /*<<< orphan*/  RST_FO ; 
 int RST_FO_FR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  ifdown ; 
 int /*<<< orphan*/  ifup ; 
 unsigned long jiffies ; 
 unsigned long max (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_clear_routing_entries (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_mb_set_mgmnt_traffic_ctl (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_wait_fifo_empty (struct ql_adapter*) ; 
 int /*<<< orphan*/  ql_write32 (struct ql_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static int ql_adapter_reset(struct ql_adapter *qdev)
{
	u32 value;
	int status = 0;
	unsigned long end_jiffies;

	/* Clear all the entries in the routing table. */
	status = ql_clear_routing_entries(qdev);
	if (status) {
		netif_err(qdev, ifup, qdev->ndev, "Failed to clear routing bits.\n");
		return status;
	}

	end_jiffies = jiffies +
		max((unsigned long)1, usecs_to_jiffies(30));

	/* Check if bit is set then skip the mailbox command and
	 * clear the bit, else we are in normal reset process.
	 */
	if (!test_bit(QL_ASIC_RECOVERY, &qdev->flags)) {
		/* Stop management traffic. */
		ql_mb_set_mgmnt_traffic_ctl(qdev, MB_SET_MPI_TFK_STOP);

		/* Wait for the NIC and MGMNT FIFOs to empty. */
		ql_wait_fifo_empty(qdev);
	} else
		clear_bit(QL_ASIC_RECOVERY, &qdev->flags);

	ql_write32(qdev, RST_FO, (RST_FO_FR << 16) | RST_FO_FR);

	do {
		value = ql_read32(qdev, RST_FO);
		if ((value & RST_FO_FR) == 0)
			break;
		cpu_relax();
	} while (time_before(jiffies, end_jiffies));

	if (value & RST_FO_FR) {
		netif_err(qdev, ifdown, qdev->ndev,
			  "ETIMEDOUT!!! errored out of resetting the chip!\n");
		status = -ETIMEDOUT;
	}

	/* Resume management traffic. */
	ql_mb_set_mgmnt_traffic_ctl(qdev, MB_SET_MPI_TFK_RESUME);
	return status;
}