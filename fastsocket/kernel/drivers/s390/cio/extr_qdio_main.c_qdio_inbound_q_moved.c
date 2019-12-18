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
struct TYPE_3__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_4__ {TYPE_1__ in; } ;
struct qdio_q {int last_move; TYPE_2__ u; int /*<<< orphan*/  irq_ptr; scalar_t__ qdio_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACHINE_IS_VM ; 
 int get_inbound_buffer_frontier (struct qdio_q*) ; 
 int /*<<< orphan*/  get_usecs () ; 
 int /*<<< orphan*/  is_thinint_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qdio_inbound_q_moved(struct qdio_q *q)
{
	int bufnr;

	bufnr = get_inbound_buffer_frontier(q);

	if ((bufnr != q->last_move) || q->qdio_error) {
		q->last_move = bufnr;
		if (!is_thinint_irq(q->irq_ptr) && !MACHINE_IS_VM)
			q->u.in.timestamp = get_usecs();
		return 1;
	} else
		return 0;
}