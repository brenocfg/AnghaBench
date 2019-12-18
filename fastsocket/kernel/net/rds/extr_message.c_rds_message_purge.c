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
struct TYPE_6__ {scalar_t__ op_rdma_mr; scalar_t__ op_active; } ;
struct TYPE_5__ {scalar_t__ op_rdma_mr; scalar_t__ op_active; } ;
struct TYPE_4__ {unsigned long op_nents; int /*<<< orphan*/ * op_sg; } ;
struct rds_message {TYPE_3__ atomic; TYPE_2__ rdma; TYPE_1__ data; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDS_MSG_PAGEVEC ; 
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  rds_atomic_free_op (TYPE_3__*) ; 
 int /*<<< orphan*/  rds_mr_put (scalar_t__) ; 
 int /*<<< orphan*/  rds_rdma_free_op (TYPE_2__*) ; 
 int /*<<< orphan*/  rdsdebug (char*,void*) ; 
 scalar_t__ sg_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rds_message_purge(struct rds_message *rm)
{
	unsigned long i;

	if (unlikely(test_bit(RDS_MSG_PAGEVEC, &rm->m_flags)))
		return;

	for (i = 0; i < rm->data.op_nents; i++) {
		rdsdebug("putting data page %p\n", (void *)sg_page(&rm->data.op_sg[i]));
		/* XXX will have to put_page for page refs */
		__free_page(sg_page(&rm->data.op_sg[i]));
	}
	rm->data.op_nents = 0;

	if (rm->rdma.op_active)
		rds_rdma_free_op(&rm->rdma);
	if (rm->rdma.op_rdma_mr)
		rds_mr_put(rm->rdma.op_rdma_mr);

	if (rm->atomic.op_active)
		rds_atomic_free_op(&rm->atomic);
	if (rm->atomic.op_rdma_mr)
		rds_mr_put(rm->atomic.op_rdma_mr);
}