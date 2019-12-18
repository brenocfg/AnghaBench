#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct workqueue_struct {int dummy; } ;
struct qlcnic_vport {int spoofchk; int /*<<< orphan*/  mac; int /*<<< orphan*/  max_tx_bw; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_list; } ;
struct qlcnic_back_channel {struct workqueue_struct* bc_trans_wq; struct workqueue_struct* bc_async_wq; int /*<<< orphan*/  async_list; } ;
struct qlcnic_vf_info {int num_vfs; struct qlcnic_vf_info* vf_info; struct qlcnic_vport* vp; int /*<<< orphan*/  trans_work; int /*<<< orphan*/  ch_free_cmpl; TYPE_2__ rcv_pend; TYPE_1__ rcv_act; int /*<<< orphan*/  send_cmd_lock; int /*<<< orphan*/  pci_func; struct qlcnic_adapter* adapter; struct qlcnic_back_channel bc; } ;
struct qlcnic_sriov {int num_vfs; struct qlcnic_sriov* vf_info; struct qlcnic_vport* vp; int /*<<< orphan*/  trans_work; int /*<<< orphan*/  ch_free_cmpl; TYPE_2__ rcv_pend; TYPE_1__ rcv_act; int /*<<< orphan*/  send_cmd_lock; int /*<<< orphan*/  pci_func; struct qlcnic_adapter* adapter; struct qlcnic_back_channel bc; } ;
struct qlcnic_adapter {TYPE_4__* ahw; TYPE_3__* pdev; } ;
struct TYPE_8__ {struct qlcnic_vf_info* sriov; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_BW ; 
 struct workqueue_struct* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_vf_info*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_enable_check (struct qlcnic_adapter*) ; 
 scalar_t__ qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_process_bc_cmd ; 
 int /*<<< orphan*/  qlcnic_sriov_virtid_fn (struct qlcnic_adapter*,int) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int qlcnic_sriov_init(struct qlcnic_adapter *adapter, int num_vfs)
{
	struct qlcnic_sriov *sriov;
	struct qlcnic_back_channel *bc;
	struct workqueue_struct *wq;
	struct qlcnic_vport *vp;
	struct qlcnic_vf_info *vf;
	int err, i;

	if (!qlcnic_sriov_enable_check(adapter))
		return -EIO;

	sriov  = kzalloc(sizeof(struct qlcnic_sriov), GFP_KERNEL);
	if (!sriov)
		return -ENOMEM;

	adapter->ahw->sriov = sriov;
	sriov->num_vfs = num_vfs;
	bc = &sriov->bc;
	sriov->vf_info = kzalloc(sizeof(struct qlcnic_vf_info) *
				 num_vfs, GFP_KERNEL);
	if (!sriov->vf_info) {
		err = -ENOMEM;
		goto qlcnic_free_sriov;
	}

	wq = create_singlethread_workqueue("bc-trans");
	if (wq == NULL) {
		err = -ENOMEM;
		dev_err(&adapter->pdev->dev,
			"Cannot create bc-trans workqueue\n");
		goto qlcnic_free_vf_info;
	}

	bc->bc_trans_wq = wq;

	wq = create_singlethread_workqueue("async");
	if (wq == NULL) {
		err = -ENOMEM;
		dev_err(&adapter->pdev->dev, "Cannot create async workqueue\n");
		goto qlcnic_destroy_trans_wq;
	}

	bc->bc_async_wq =  wq;
	INIT_LIST_HEAD(&bc->async_list);

	for (i = 0; i < num_vfs; i++) {
		vf = &sriov->vf_info[i];
		vf->adapter = adapter;
		vf->pci_func = qlcnic_sriov_virtid_fn(adapter, i);
		mutex_init(&vf->send_cmd_lock);
		INIT_LIST_HEAD(&vf->rcv_act.wait_list);
		INIT_LIST_HEAD(&vf->rcv_pend.wait_list);
		spin_lock_init(&vf->rcv_act.lock);
		spin_lock_init(&vf->rcv_pend.lock);
		init_completion(&vf->ch_free_cmpl);

		INIT_WORK(&vf->trans_work, qlcnic_sriov_process_bc_cmd);

		if (qlcnic_sriov_pf_check(adapter)) {
			vp = kzalloc(sizeof(struct qlcnic_vport), GFP_KERNEL);
			if (!vp) {
				err = -ENOMEM;
				goto qlcnic_destroy_async_wq;
			}
			sriov->vf_info[i].vp = vp;
			vp->max_tx_bw = MAX_BW;
			vp->spoofchk = true;
			random_ether_addr(vp->mac);
			dev_info(&adapter->pdev->dev,
				 "MAC Address %pM is configured for VF %d\n",
				 vp->mac, i);
		}
	}

	return 0;

qlcnic_destroy_async_wq:
	destroy_workqueue(bc->bc_async_wq);

qlcnic_destroy_trans_wq:
	destroy_workqueue(bc->bc_trans_wq);

qlcnic_free_vf_info:
	kfree(sriov->vf_info);

qlcnic_free_sriov:
	kfree(adapter->ahw->sriov);
	return err;
}