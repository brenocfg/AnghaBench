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
typedef  int u32 ;
struct TYPE_2__ {int dbid; } ;
struct ocrdma_qp {int /*<<< orphan*/  rq_db; TYPE_1__ rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ ) ; 
 int ocrdma_get_num_posted_shift (struct ocrdma_qp*) ; 

__attribute__((used)) static void ocrdma_ring_rq_db(struct ocrdma_qp *qp)
{
	u32 val = qp->rq.dbid | (1 << ocrdma_get_num_posted_shift(qp));

	iowrite32(val, qp->rq_db);
}