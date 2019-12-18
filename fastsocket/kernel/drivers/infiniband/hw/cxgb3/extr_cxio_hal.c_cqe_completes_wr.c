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
struct t3_wq {int /*<<< orphan*/  rq_wptr; int /*<<< orphan*/  rq_rptr; } ;
struct t3_cqe {int dummy; } ;

/* Variables and functions */
 scalar_t__ CQE_OPCODE (struct t3_cqe) ; 
 scalar_t__ CQE_SEND_OPCODE (struct t3_cqe) ; 
 scalar_t__ Q_EMPTY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RQ_TYPE (struct t3_cqe) ; 
 scalar_t__ SQ_TYPE (struct t3_cqe) ; 
 scalar_t__ T3_RDMA_WRITE ; 
 scalar_t__ T3_READ_RESP ; 
 scalar_t__ T3_TERMINATE ; 

__attribute__((used)) static int cqe_completes_wr(struct t3_cqe *cqe, struct t3_wq *wq)
{
	if (CQE_OPCODE(*cqe) == T3_TERMINATE)
		return 0;

	if ((CQE_OPCODE(*cqe) == T3_RDMA_WRITE) && RQ_TYPE(*cqe))
		return 0;

	if ((CQE_OPCODE(*cqe) == T3_READ_RESP) && SQ_TYPE(*cqe))
		return 0;

	if (CQE_SEND_OPCODE(*cqe) && RQ_TYPE(*cqe) &&
	    Q_EMPTY(wq->rq_rptr, wq->rq_wptr))
		return 0;

	return 1;
}