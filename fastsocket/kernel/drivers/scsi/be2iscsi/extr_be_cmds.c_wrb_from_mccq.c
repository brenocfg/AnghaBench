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
struct be_queue_info {scalar_t__ len; int head; int /*<<< orphan*/  used; } ;
struct TYPE_3__ {struct be_queue_info q; } ;
struct TYPE_4__ {TYPE_1__ mcc_obj; } ;
struct beiscsi_hba {TYPE_2__ ctrl; } ;
struct be_mcc_wrb {int tag0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_head_inc (struct be_queue_info*) ; 
 struct be_mcc_wrb* queue_head_node (struct be_queue_info*) ; 

struct be_mcc_wrb *wrb_from_mccq(struct beiscsi_hba *phba)
{
	struct be_queue_info *mccq = &phba->ctrl.mcc_obj.q;
	struct be_mcc_wrb *wrb;

	BUG_ON(atomic_read(&mccq->used) >= mccq->len);
	wrb = queue_head_node(mccq);
	memset(wrb, 0, sizeof(*wrb));
	wrb->tag0 = (mccq->head & 0x000000FF) << 16;
	queue_head_inc(mccq);
	atomic_inc(&mccq->used);
	return wrb;
}