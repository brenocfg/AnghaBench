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
struct TYPE_2__ {int /*<<< orphan*/  max_sge; scalar_t__ size; } ;
struct qib_srq {int /*<<< orphan*/  limit; TYPE_1__ rq; } ;
struct ib_srq_attr {int /*<<< orphan*/  srq_limit; int /*<<< orphan*/  max_sge; scalar_t__ max_wr; } ;
struct ib_srq {int dummy; } ;

/* Variables and functions */
 struct qib_srq* to_isrq (struct ib_srq*) ; 

int qib_query_srq(struct ib_srq *ibsrq, struct ib_srq_attr *attr)
{
	struct qib_srq *srq = to_isrq(ibsrq);

	attr->max_wr = srq->rq.size - 1;
	attr->max_sge = srq->rq.max_sge;
	attr->srq_limit = srq->limit;
	return 0;
}