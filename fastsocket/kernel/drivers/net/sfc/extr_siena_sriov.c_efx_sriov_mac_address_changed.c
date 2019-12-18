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
struct vfdi_status {TYPE_2__* peers; } ;
struct TYPE_4__ {struct vfdi_status* addr; } ;
struct efx_nic {int /*<<< orphan*/  peer_work; TYPE_3__* net_dev; int /*<<< orphan*/  vf_init_count; TYPE_1__ vfdi_status; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfdi_workqueue ; 

void efx_sriov_mac_address_changed(struct efx_nic *efx)
{
	struct vfdi_status *vfdi_status = efx->vfdi_status.addr;

	if (!efx->vf_init_count)
		return;
	memcpy(vfdi_status->peers[0].mac_addr,
	       efx->net_dev->dev_addr, ETH_ALEN);
	queue_work(vfdi_workqueue, &efx->peer_work);
}