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
struct request_queue {struct mtd_blktrans_ops* queuedata; } ;
struct mtd_blktrans_ops {TYPE_1__* blkcore_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtd_blktrans_request(struct request_queue *rq)
{
	struct mtd_blktrans_ops *tr = rq->queuedata;
	wake_up_process(tr->blkcore_priv->thread);
}