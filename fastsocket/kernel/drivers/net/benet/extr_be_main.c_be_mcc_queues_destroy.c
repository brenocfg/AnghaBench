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
struct be_queue_info {scalar_t__ created; } ;
struct TYPE_2__ {struct be_queue_info cq; struct be_queue_info q; } ;
struct be_adapter {TYPE_1__ mcc_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  QTYPE_CQ ; 
 int /*<<< orphan*/  QTYPE_MCCQ ; 
 int /*<<< orphan*/  be_cmd_q_destroy (struct be_adapter*,struct be_queue_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be_queue_free (struct be_adapter*,struct be_queue_info*) ; 

__attribute__((used)) static void be_mcc_queues_destroy(struct be_adapter *adapter)
{
	struct be_queue_info *q;

	q = &adapter->mcc_obj.q;
	if (q->created)
		be_cmd_q_destroy(adapter, q, QTYPE_MCCQ);
	be_queue_free(adapter, q);

	q = &adapter->mcc_obj.cq;
	if (q->created)
		be_cmd_q_destroy(adapter, q, QTYPE_CQ);
	be_queue_free(adapter, q);
}