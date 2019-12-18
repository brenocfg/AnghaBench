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
typedef  int /*<<< orphan*/  u32 ;
struct c2_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct c2_cq {TYPE_1__ ibcq; } ;

/* Variables and functions */
 struct c2_cq* c2_cq_get (struct c2_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c2_cq_put (struct c2_cq*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void c2_cq_event(struct c2_dev *c2dev, u32 mq_index)
{
	struct c2_cq *cq;

	cq = c2_cq_get(c2dev, mq_index);
	if (!cq) {
		printk("discarding events on destroyed CQN=%d\n", mq_index);
		return;
	}

	(*cq->ibcq.comp_handler) (&cq->ibcq, cq->ibcq.cq_context);
	c2_cq_put(cq);
}