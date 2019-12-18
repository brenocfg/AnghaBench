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
struct qeth_qdio_out_q {int next_buf_to_fill; int do_pack; int /*<<< orphan*/  state; TYPE_3__* card; int /*<<< orphan*/  set_pci_flags_count; int /*<<< orphan*/  used_buffers; } ;
struct TYPE_5__ {int bufs_sent_pack; } ;
struct TYPE_4__ {scalar_t__ performance_stats; } ;
struct TYPE_6__ {TYPE_2__ perf_stats; TYPE_1__ options; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ QETH_LOW_WATERMARK_PACK ; 
 int /*<<< orphan*/  QETH_OUT_Q_LOCKED_FLUSH ; 
 scalar_t__ QETH_OUT_Q_UNLOCKED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_flush_buffers (struct qeth_qdio_out_q*,int,int) ; 
 scalar_t__ qeth_flush_buffers_on_no_pci (struct qeth_qdio_out_q*) ; 
 scalar_t__ qeth_switch_to_nonpacking_if_needed (struct qeth_qdio_out_q*) ; 

__attribute__((used)) static void qeth_check_outbound_queue(struct qeth_qdio_out_q *queue)
{
	int index;
	int flush_cnt = 0;
	int q_was_packing = 0;

	/*
	 * check if weed have to switch to non-packing mode or if
	 * we have to get a pci flag out on the queue
	 */
	if ((atomic_read(&queue->used_buffers) <= QETH_LOW_WATERMARK_PACK) ||
	    !atomic_read(&queue->set_pci_flags_count)) {
		if (atomic_xchg(&queue->state, QETH_OUT_Q_LOCKED_FLUSH) ==
				QETH_OUT_Q_UNLOCKED) {
			/*
			 * If we get in here, there was no action in
			 * do_send_packet. So, we check if there is a
			 * packing buffer to be flushed here.
			 */
			netif_stop_queue(queue->card->dev);
			index = queue->next_buf_to_fill;
			q_was_packing = queue->do_pack;
			/* queue->do_pack may change */
			barrier();
			flush_cnt += qeth_switch_to_nonpacking_if_needed(queue);
			if (!flush_cnt &&
			    !atomic_read(&queue->set_pci_flags_count))
				flush_cnt +=
					qeth_flush_buffers_on_no_pci(queue);
			if (queue->card->options.performance_stats &&
			    q_was_packing)
				queue->card->perf_stats.bufs_sent_pack +=
					flush_cnt;
			if (flush_cnt)
				qeth_flush_buffers(queue, index, flush_cnt);
			atomic_set(&queue->state, QETH_OUT_Q_UNLOCKED);
		}
	}
}