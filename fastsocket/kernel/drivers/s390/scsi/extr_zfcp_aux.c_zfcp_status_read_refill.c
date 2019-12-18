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
struct zfcp_adapter {int /*<<< orphan*/  stat_miss; int /*<<< orphan*/  qdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ zfcp_fsf_status_read (int /*<<< orphan*/ ) ; 

int zfcp_status_read_refill(struct zfcp_adapter *adapter)
{
	while (atomic_read(&adapter->stat_miss) > 0)
		if (zfcp_fsf_status_read(adapter->qdio)) {
			if (atomic_read(&adapter->stat_miss) >= 16) {
				zfcp_erp_adapter_reopen(adapter, 0, "axsref1",
							NULL);
				return 1;
			}
			break;
		} else
			atomic_dec(&adapter->stat_miss);
	return 0;
}