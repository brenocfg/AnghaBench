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
typedef  int u32 ;
struct TYPE_5__ {int num_cqs; } ;
struct TYPE_4__ {int /*<<< orphan*/  cq; } ;
struct mthca_dev {TYPE_2__ limits; TYPE_1__ cq_table; } ;
struct TYPE_6__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct mthca_cq {TYPE_3__ ibcq; int /*<<< orphan*/  arm_sn; } ;

/* Variables and functions */
 struct mthca_cq* mthca_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void mthca_cq_completion(struct mthca_dev *dev, u32 cqn)
{
	struct mthca_cq *cq;

	cq = mthca_array_get(&dev->cq_table.cq, cqn & (dev->limits.num_cqs - 1));

	if (!cq) {
		mthca_warn(dev, "Completion event for bogus CQ %08x\n", cqn);
		return;
	}

	++cq->arm_sn;

	cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);
}