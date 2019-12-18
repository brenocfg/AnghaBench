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
struct efx_vf {unsigned int index; int rx_filter_id; int tx_filter_id; int /*<<< orphan*/  txq_lock; int /*<<< orphan*/  status_lock; int /*<<< orphan*/  flush_waitq; int /*<<< orphan*/  reset_work; int /*<<< orphan*/  req; int /*<<< orphan*/  tx_filter_mode; struct efx_nic* efx; } ;
struct efx_nic {int vf_count; struct efx_vf* vf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VF_TX_FILTER_AUTO ; 
 int /*<<< orphan*/  efx_sriov_reset_vf_work ; 
 int /*<<< orphan*/  efx_sriov_vfdi ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct efx_vf* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_sriov_vf_alloc(struct efx_nic *efx)
{
	unsigned index;
	struct efx_vf *vf;

	efx->vf = kzalloc(sizeof(struct efx_vf) * efx->vf_count, GFP_KERNEL);
	if (!efx->vf)
		return -ENOMEM;

	for (index = 0; index < efx->vf_count; ++index) {
		vf = efx->vf + index;

		vf->efx = efx;
		vf->index = index;
		vf->rx_filter_id = -1;
		vf->tx_filter_mode = VF_TX_FILTER_AUTO;
		vf->tx_filter_id = -1;
		INIT_WORK(&vf->req, efx_sriov_vfdi);
		INIT_WORK(&vf->reset_work, efx_sriov_reset_vf_work);
		init_waitqueue_head(&vf->flush_waitq);
		mutex_init(&vf->status_lock);
		mutex_init(&vf->txq_lock);
	}

	return 0;
}