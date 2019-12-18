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
struct cnic_local {int (* start_cm ) (struct cnic_dev*) ;int /*<<< orphan*/ * ulp_ops; struct cnic_dev** ulp_handle; int /*<<< orphan*/  delete_task; } ;
struct cnic_dev {int /*<<< orphan*/  cm_select_dev; int /*<<< orphan*/  cm_close; int /*<<< orphan*/  cm_abort; int /*<<< orphan*/  cm_connect; int /*<<< orphan*/  cm_destroy; int /*<<< orphan*/  cm_create; struct cnic_local* cnic_priv; } ;

/* Variables and functions */
 size_t CNIC_ULP_L4 ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_ulp_ops ; 
 int /*<<< orphan*/  cnic_cm_abort ; 
 int cnic_cm_alloc_mem (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_cm_close ; 
 int /*<<< orphan*/  cnic_cm_connect ; 
 int /*<<< orphan*/  cnic_cm_create ; 
 int /*<<< orphan*/  cnic_cm_destroy ; 
 int /*<<< orphan*/  cnic_cm_free_mem (struct cnic_dev*) ; 
 int /*<<< orphan*/  cnic_cm_select_dev ; 
 int /*<<< orphan*/  cnic_delete_task ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct cnic_dev*) ; 

__attribute__((used)) static int cnic_cm_open(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	int err;

	err = cnic_cm_alloc_mem(dev);
	if (err)
		return err;

	err = cp->start_cm(dev);

	if (err)
		goto err_out;

	INIT_DELAYED_WORK(&cp->delete_task, cnic_delete_task);

	dev->cm_create = cnic_cm_create;
	dev->cm_destroy = cnic_cm_destroy;
	dev->cm_connect = cnic_cm_connect;
	dev->cm_abort = cnic_cm_abort;
	dev->cm_close = cnic_cm_close;
	dev->cm_select_dev = cnic_cm_select_dev;

	cp->ulp_handle[CNIC_ULP_L4] = dev;
	rcu_assign_pointer(cp->ulp_ops[CNIC_ULP_L4], &cm_ulp_ops);
	return 0;

err_out:
	cnic_cm_free_mem(dev);
	return err;
}