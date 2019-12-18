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
typedef  int /*<<< orphan*/  u16 ;
struct ocrdma_dev {int eq_cnt; int /*<<< orphan*/  dev_lock; TYPE_2__* qp_eq_tbl; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int cq_cnt; TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 ocrdma_bind_eq(struct ocrdma_dev *dev)
{
	int i, selected_eq = 0, cq_cnt = 0;
	u16 eq_id;

	mutex_lock(&dev->dev_lock);
	cq_cnt = dev->qp_eq_tbl[0].cq_cnt;
	eq_id = dev->qp_eq_tbl[0].q.id;
	/* find the EQ which is has the least number of
	 * CQs associated with it.
	 */
	for (i = 0; i < dev->eq_cnt; i++) {
		if (dev->qp_eq_tbl[i].cq_cnt < cq_cnt) {
			cq_cnt = dev->qp_eq_tbl[i].cq_cnt;
			eq_id = dev->qp_eq_tbl[i].q.id;
			selected_eq = i;
		}
	}
	dev->qp_eq_tbl[selected_eq].cq_cnt += 1;
	mutex_unlock(&dev->dev_lock);
	return eq_id;
}