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
struct qdio_q {int first_to_check; int /*<<< orphan*/  nr; TYPE_2__* irq_ptr; TYPE_1__ q_stats; int /*<<< orphan*/  nr_buf_used; } ;
struct TYPE_4__ {int /*<<< orphan*/  perf_stat_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 scalar_t__ QDIO_IQDIO_QFMT ; 
 int /*<<< orphan*/  QDIO_MAX_BUFFERS_MASK ; 
#define  SLSB_CU_OUTPUT_PRIMED 133 
#define  SLSB_P_OUTPUT_EMPTY 132 
#define  SLSB_P_OUTPUT_ERROR 131 
#define  SLSB_P_OUTPUT_HALTED 130 
#define  SLSB_P_OUTPUT_NOT_INIT 129 
#define  SLSB_P_OUTPUT_PENDING 128 
 int /*<<< orphan*/  account_sbals (struct qdio_q*,int) ; 
 int /*<<< orphan*/  account_sbals_error (struct qdio_q*,int) ; 
 void* add_buf (int,int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int get_buf_states (struct qdio_q*,int,unsigned char*,int,int /*<<< orphan*/ ,int) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ multicast_outbound (struct qdio_q*) ; 
 int /*<<< orphan*/  pci_out_supported (struct qdio_q*) ; 
 int /*<<< orphan*/  process_buffer_error (struct qdio_q*,int) ; 
 int /*<<< orphan*/  qdio_siga_sync_q (struct qdio_q*) ; 
 scalar_t__ queue_type (struct qdio_q*) ; 

__attribute__((used)) static int get_outbound_buffer_frontier(struct qdio_q *q)
{
	int count, stop;
	unsigned char state;

	if (((queue_type(q) != QDIO_IQDIO_QFMT) && !pci_out_supported(q)) ||
	    (queue_type(q) == QDIO_IQDIO_QFMT && multicast_outbound(q)))
		qdio_siga_sync_q(q);

	/*
	 * Don't check 128 buffers, as otherwise qdio_inbound_q_moved
	 * would return 0.
	 */
	count = min(atomic_read(&q->nr_buf_used), QDIO_MAX_BUFFERS_MASK);
	stop = add_buf(q->first_to_check, count);
	if (q->first_to_check == stop)
		goto out;

	count = get_buf_states(q, q->first_to_check, &state, count, 0, 1);
	if (!count)
		goto out;

	switch (state) {
	case SLSB_P_OUTPUT_PENDING:
		BUG();
	case SLSB_P_OUTPUT_EMPTY:
		/* the adapter got it */
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr,
			"out empty:%1d %02x", q->nr, count);

		atomic_sub(count, &q->nr_buf_used);
		q->first_to_check = add_buf(q->first_to_check, count);
		if (q->irq_ptr->perf_stat_enabled)
			account_sbals(q, count);

		break;
	case SLSB_P_OUTPUT_ERROR:
		process_buffer_error(q, count);
		q->first_to_check = add_buf(q->first_to_check, count);
		atomic_sub(count, &q->nr_buf_used);
		if (q->irq_ptr->perf_stat_enabled)
			account_sbals_error(q, count);
		break;
	case SLSB_CU_OUTPUT_PRIMED:
		/* the adapter has not fetched the output yet */
		if (q->irq_ptr->perf_stat_enabled)
			q->q_stats.nr_sbal_nop++;
		DBF_DEV_EVENT(DBF_INFO, q->irq_ptr, "out primed:%1d",
			      q->nr);
		break;
	case SLSB_P_OUTPUT_NOT_INIT:
	case SLSB_P_OUTPUT_HALTED:
		break;
	default:
		BUG();
	}

out:
	return q->first_to_check;
}