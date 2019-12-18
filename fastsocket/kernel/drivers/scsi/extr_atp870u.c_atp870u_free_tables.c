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
struct atp_unit {TYPE_1__** id; int /*<<< orphan*/  pdev; } ;
struct Scsi_Host {int /*<<< orphan*/  hostdata; } ;
struct TYPE_2__ {int /*<<< orphan*/ * prd_table; int /*<<< orphan*/  prd_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atp870u_free_tables(struct Scsi_Host *host)
{
	struct atp_unit *atp_dev = (struct atp_unit *)&host->hostdata;
	int j, k;
	for (j=0; j < 2; j++) {
		for (k = 0; k < 16; k++) {
			if (!atp_dev->id[j][k].prd_table)
				continue;
			pci_free_consistent(atp_dev->pdev, 1024, atp_dev->id[j][k].prd_table, atp_dev->id[j][k].prd_bus);
			atp_dev->id[j][k].prd_table = NULL;
		}
	}
}