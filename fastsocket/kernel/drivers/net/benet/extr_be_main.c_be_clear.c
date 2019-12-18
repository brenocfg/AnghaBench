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
struct be_adapter {int uc_macs; int /*<<< orphan*/ * pmac_id; int /*<<< orphan*/  if_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cancel_worker (struct be_adapter*) ; 
 int /*<<< orphan*/  be_clear_queues (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_if_destroy (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_cmd_pmac_del (struct be_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_msix_disable (struct be_adapter*) ; 
 int /*<<< orphan*/  be_vf_clear (struct be_adapter*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ sriov_enabled (struct be_adapter*) ; 

__attribute__((used)) static int be_clear(struct be_adapter *adapter)
{
	int i;

	be_cancel_worker(adapter);

	if (sriov_enabled(adapter))
		be_vf_clear(adapter);

	/* delete the primary mac along with the uc-mac list */
	for (i = 0; i < (adapter->uc_macs + 1); i++)
		be_cmd_pmac_del(adapter, adapter->if_handle,
				adapter->pmac_id[i], 0);
	adapter->uc_macs = 0;

	be_cmd_if_destroy(adapter, adapter->if_handle,  0);

	be_clear_queues(adapter);

	kfree(adapter->pmac_id);
	adapter->pmac_id = NULL;

	be_msix_disable(adapter);
	return 0;
}