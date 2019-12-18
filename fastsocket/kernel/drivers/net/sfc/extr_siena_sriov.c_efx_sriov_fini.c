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
struct efx_vf {int /*<<< orphan*/  reset_work; int /*<<< orphan*/  req; } ;
struct efx_nic {scalar_t__ vf_init_count; unsigned int vf_count; int /*<<< orphan*/  vfdi_status; struct efx_vf* vf; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  peer_work; TYPE_1__* vfdi_channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_sriov_cmd (struct efx_nic*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_sriov_free_local (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_sriov_usrev (struct efx_nic*,int) ; 
 int /*<<< orphan*/  efx_sriov_vfs_fini (struct efx_nic*) ; 
 int /*<<< orphan*/  kfree (struct efx_vf*) ; 
 int /*<<< orphan*/  pci_disable_sriov (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

void efx_sriov_fini(struct efx_nic *efx)
{
	struct efx_vf *vf;
	unsigned int pos;

	if (efx->vf_init_count == 0)
		return;

	/* Disable all interfaces to reconfiguration */
	BUG_ON(efx->vfdi_channel->enabled);
	efx_sriov_usrev(efx, false);
	rtnl_lock();
	efx->vf_init_count = 0;
	rtnl_unlock();

	/* Flush all reconfiguration work */
	for (pos = 0; pos < efx->vf_count; ++pos) {
		vf = efx->vf + pos;
		cancel_work_sync(&vf->req);
		cancel_work_sync(&vf->reset_work);
	}
	cancel_work_sync(&efx->peer_work);

	pci_disable_sriov(efx->pci_dev);

	/* Tear down back-end state */
	efx_sriov_vfs_fini(efx);
	efx_sriov_free_local(efx);
	kfree(efx->vf);
	efx_nic_free_buffer(efx, &efx->vfdi_status);
	efx_sriov_cmd(efx, false, NULL, NULL);
}