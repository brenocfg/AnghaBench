#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct t3_cqe {int dummy; } ;
struct t3_cq {int /*<<< orphan*/  size_log2; int /*<<< orphan*/  rptr; struct t3_cqe* queue; int /*<<< orphan*/  sw_rptr; struct t3_cqe* sw_queue; int /*<<< orphan*/  sw_wptr; } ;

/* Variables and functions */
 scalar_t__ CQ_VLD_ENTRY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct t3_cqe*) ; 
 int /*<<< orphan*/  Q_EMPTY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Q_PTR2IDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct t3_cqe *cxio_next_cqe(struct t3_cq *cq)
{
	struct t3_cqe *cqe;

	if (!Q_EMPTY(cq->sw_rptr, cq->sw_wptr)) {
		cqe = cq->sw_queue + (Q_PTR2IDX(cq->sw_rptr, cq->size_log2));
		return cqe;
	}
	cqe = cq->queue + (Q_PTR2IDX(cq->rptr, cq->size_log2));
	if (CQ_VLD_ENTRY(cq->rptr, cq->size_log2, cqe))
		return cqe;
	return NULL;
}