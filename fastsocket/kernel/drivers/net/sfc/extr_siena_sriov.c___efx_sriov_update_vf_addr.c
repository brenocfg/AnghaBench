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
struct efx_vf {TYPE_1__* efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  peer_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_sriov_reset_rx_filter (struct efx_vf*) ; 
 int /*<<< orphan*/  efx_sriov_reset_tx_filter (struct efx_vf*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfdi_workqueue ; 

__attribute__((used)) static void __efx_sriov_update_vf_addr(struct efx_vf *vf)
{
	efx_sriov_reset_tx_filter(vf);
	efx_sriov_reset_rx_filter(vf);
	queue_work(vfdi_workqueue, &vf->efx->peer_work);
}