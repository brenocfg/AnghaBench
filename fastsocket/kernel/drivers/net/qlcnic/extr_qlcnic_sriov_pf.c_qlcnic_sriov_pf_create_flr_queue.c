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
struct workqueue_struct {int dummy; } ;
struct qlcnic_back_channel {struct workqueue_struct* bc_flr_wq; } ;
struct qlcnic_adapter {TYPE_3__* pdev; TYPE_2__* ahw; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {TYPE_1__* sriov; } ;
struct TYPE_4__ {struct qlcnic_back_channel bc; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct workqueue_struct* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int qlcnic_sriov_pf_create_flr_queue(struct qlcnic_adapter *adapter)
{
	struct qlcnic_back_channel *bc = &adapter->ahw->sriov->bc;
	struct workqueue_struct *wq;

	wq = create_singlethread_workqueue("qlcnic-flr");
	if (wq == NULL) {
		dev_err(&adapter->pdev->dev, "Cannot create FLR workqueue\n");
		return -ENOMEM;
	}

	bc->bc_flr_wq =  wq;
	return 0;
}