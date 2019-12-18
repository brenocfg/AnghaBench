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
struct TYPE_3__ {int /*<<< orphan*/  nr_sbal_nop; } ;
struct qdio_q {int first_to_check; TYPE_2__* irq_ptr; TYPE_1__ q_stats; int /*<<< orphan*/  nr_buf_used; } ;
struct TYPE_4__ {int /*<<< orphan*/  perf_stat_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int /*<<< orphan*/  QDIO_MAX_BUFFERS_MASK ; 
#define  SLSB_CU_INPUT_EMPTY 132 
#define  SLSB_P_INPUT_ACK 131 
#define  SLSB_P_INPUT_ERROR 130 
#define  SLSB_P_INPUT_NOT_INIT 129 
#define  SLSB_P_INPUT_PRIMED 128 
 int /*<<< orphan*/  account_sbals (struct qdio_q*,int) ; 
 int /*<<< orphan*/  account_sbals_error (struct qdio_q*,int) ; 
 void* add_buf (int,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int get_buf_states (struct qdio_q*,int,unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inbound_primed (struct qdio_q*,int) ; 
 int /*<<< orphan*/  inbound_queue_full ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_buffer_error (struct qdio_q*,int) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_inbound_buffer_frontier(struct qdio_q *q)
{
	int count, stop;
	unsigned char state;

	/*
	 * Don't check 128 buffers, as otherwise qdio_inbound_q_moved
	 * would return 0.
	 */
	count = min(atomic_read(&q->nr_buf_used), QDIO_MAX_BUFFERS_MASK);
	stop = add_buf(q->first_to_check, count);

	if (q->first_to_check == stop)
		goto out;

	/*
	 * No siga sync here, as a PCI or we after a thin interrupt
	 * already sync'ed the queues.
	 */
	count = get_buf_states(q, q->first_to_check, &state, count, 1, 0);
	if (!count)
		goto out;

	switch (state) {
	case SLSB_P_INPUT_PRIMED:
		inbound_primed(q, count);
		q->first_to_check = add_buf(q->first_to_check, count);
		if (atomic_sub(count, &q->nr_buf_used) == 0)
			qperf_inc(q, inbound_queue_full);
		if (q->irq_ptr->perf_stat_enabled)
			account_sbals(q, count);
		break;
	case SLSB_P_INPUT_ERROR:
		process_buffer_error(q, count);
		q->first_to_check = add_buf(q->first_to_check, count);
		atomic_sub(count, &q->nr_buf_used);
		if (q->irq_ptr->perf_stat_enabled)
			account_sbals_error(q, count);
		break;
	case SLSB_CU_INPUT_EMPTY:
	case SLSB_P_INPUT_NOT_INIT:
	case SLSB_P_INPUT_ACK:
		if (q->irq_ptr->perf_stat_enabled)
			q->q_stats.nr_sbal_nop++;
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "in nop");
		break;
	default:
		BUG();
	}
out:
	return q->first_to_check;
}