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
struct sge_txq {size_t size; unsigned int cntxt_id; int /*<<< orphan*/  db_lock; int /*<<< orphan*/ * desc; void* stat; scalar_t__ restarts; scalar_t__ stops; scalar_t__ pidx; scalar_t__ cidx; scalar_t__ in_use; } ;
struct TYPE_2__ {unsigned int egr_start; struct sge_txq** egr_map; } ;
struct adapter {TYPE_1__ sge; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_txq(struct adapter *adap, struct sge_txq *q, unsigned int id)
{
	q->in_use = 0;
	q->cidx = q->pidx = 0;
	q->stops = q->restarts = 0;
	q->stat = (void *)&q->desc[q->size];
	q->cntxt_id = id;
	spin_lock_init(&q->db_lock);
	adap->sge.egr_map[id - adap->sge.egr_start] = q;
}