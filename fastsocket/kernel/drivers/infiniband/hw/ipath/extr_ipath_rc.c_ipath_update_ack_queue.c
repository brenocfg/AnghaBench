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
struct ipath_qp {unsigned int s_tail_ack_queue; int /*<<< orphan*/  s_ack_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACKNOWLEDGE ; 
 unsigned int IPATH_MAX_RDMA_ATOMIC ; 
 int /*<<< orphan*/  OP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ipath_update_ack_queue(struct ipath_qp *qp, unsigned n)
{
	unsigned next;

	next = n + 1;
	if (next > IPATH_MAX_RDMA_ATOMIC)
		next = 0;
	if (n == qp->s_tail_ack_queue) {
		qp->s_tail_ack_queue = next;
		qp->s_ack_state = OP(ACKNOWLEDGE);
	}
}