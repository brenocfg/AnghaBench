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
struct qdio_q {int last_move; int /*<<< orphan*/  nr; int /*<<< orphan*/  irq_ptr; scalar_t__ qdio_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int get_outbound_buffer_frontier (struct qdio_q*) ; 

__attribute__((used)) static inline int qdio_outbound_q_moved(struct qdio_q *q)
{
	int bufnr;

	bufnr = get_outbound_buffer_frontier(q);

	if ((bufnr != q->last_move) || q->qdio_error) {
		q->last_move = bufnr;
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "out moved:%1d", q->nr);
		return 1;
	} else
		return 0;
}