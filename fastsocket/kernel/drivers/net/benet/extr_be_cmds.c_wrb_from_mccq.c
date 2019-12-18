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
struct be_queue_info {scalar_t__ len; int /*<<< orphan*/  used; int /*<<< orphan*/  created; } ;
struct be_mcc_wrb {int dummy; } ;
struct TYPE_2__ {struct be_queue_info q; } ;
struct be_adapter {TYPE_1__ mcc_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct be_mcc_wrb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_head_inc (struct be_queue_info*) ; 
 struct be_mcc_wrb* queue_head_node (struct be_queue_info*) ; 

__attribute__((used)) static struct be_mcc_wrb *wrb_from_mccq(struct be_adapter *adapter)
{
	struct be_queue_info *mccq = &adapter->mcc_obj.q;
	struct be_mcc_wrb *wrb;

	if (!mccq->created)
		return NULL;

	if (atomic_read(&mccq->used) >= mccq->len)
		return NULL;

	wrb = queue_head_node(mccq);
	queue_head_inc(mccq);
	atomic_inc(&mccq->used);
	memset(wrb, 0, sizeof(*wrb));
	return wrb;
}