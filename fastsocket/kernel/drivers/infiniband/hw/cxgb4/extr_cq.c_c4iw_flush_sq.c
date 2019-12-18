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
struct TYPE_2__ {int cidx; int in_use; int size; struct t4_swsqe* sw_sq; } ;
struct t4_wq {TYPE_1__ sq; } ;
struct t4_swsqe {scalar_t__ signaled; } ;
struct t4_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  insert_sq_cqe (struct t4_wq*,struct t4_cq*,struct t4_swsqe*) ; 

int c4iw_flush_sq(struct t4_wq *wq, struct t4_cq *cq, int count)
{
	int flushed = 0;
	struct t4_swsqe *swsqe = &wq->sq.sw_sq[wq->sq.cidx + count];
	int in_use = wq->sq.in_use - count;

	BUG_ON(in_use < 0);
	while (in_use--) {
		swsqe->signaled = 0;
		insert_sq_cqe(wq, cq, swsqe);
		swsqe++;
		if (swsqe == (wq->sq.sw_sq + wq->sq.size))
			swsqe = wq->sq.sw_sq;
		flushed++;
	}
	return flushed;
}