#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct be_queue_info {int dummy; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_mcc_compl {int dummy; } ;
struct TYPE_3__ {struct be_queue_info q; struct be_queue_info cq; } ;
struct be_adapter {TYPE_1__ mcc_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCC_CQ_LEN ; 
 int /*<<< orphan*/  MCC_Q_LEN ; 
 int /*<<< orphan*/  QTYPE_CQ ; 
 scalar_t__ be_cmd_cq_create (struct be_adapter*,struct be_queue_info*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ be_cmd_mccq_create (struct be_adapter*,struct be_queue_info*,struct be_queue_info*) ; 
 int /*<<< orphan*/  be_cmd_q_destroy (struct be_adapter*,struct be_queue_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ be_queue_alloc (struct be_adapter*,struct be_queue_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  be_queue_free (struct be_adapter*,struct be_queue_info*) ; 
 TYPE_2__* mcc_eqo (struct be_adapter*) ; 

__attribute__((used)) static int be_mcc_queues_create(struct be_adapter *adapter)
{
	struct be_queue_info *q, *cq;

	cq = &adapter->mcc_obj.cq;
	if (be_queue_alloc(adapter, cq, MCC_CQ_LEN,
			sizeof(struct be_mcc_compl)))
		goto err;

	/* Use the default EQ for MCC completions */
	if (be_cmd_cq_create(adapter, cq, &mcc_eqo(adapter)->q, true, 0))
		goto mcc_cq_free;

	q = &adapter->mcc_obj.q;
	if (be_queue_alloc(adapter, q, MCC_Q_LEN, sizeof(struct be_mcc_wrb)))
		goto mcc_cq_destroy;

	if (be_cmd_mccq_create(adapter, q, cq))
		goto mcc_q_free;

	return 0;

mcc_q_free:
	be_queue_free(adapter, q);
mcc_cq_destroy:
	be_cmd_q_destroy(adapter, cq, QTYPE_CQ);
mcc_cq_free:
	be_queue_free(adapter, cq);
err:
	return -1;
}