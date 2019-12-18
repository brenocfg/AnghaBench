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
struct sk_buff {int dummy; } ;
struct qeth_qdio_out_q {int next_buf_to_fill; TYPE_3__* card; int /*<<< orphan*/  set_pci_flags_count; int /*<<< orphan*/  state; struct qeth_qdio_out_buffer** bufs; scalar_t__ do_pack; } ;
struct qeth_qdio_out_buffer {int next_element_to_fill; int /*<<< orphan*/  state; } ;
struct qeth_hdr {int dummy; } ;
struct qeth_card {int dummy; } ;
struct TYPE_5__ {int bufs_sent_pack; } ;
struct TYPE_4__ {scalar_t__ performance_stats; } ;
struct TYPE_6__ {TYPE_2__ perf_stats; TYPE_1__ options; } ;

/* Variables and functions */
 int EBUSY ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 int /*<<< orphan*/  QETH_OUT_Q_LOCKED ; 
 int /*<<< orphan*/  QETH_OUT_Q_LOCKED_FLUSH ; 
 scalar_t__ QETH_OUT_Q_UNLOCKED ; 
 scalar_t__ QETH_QDIO_BUF_EMPTY ; 
 scalar_t__ QETH_QDIO_BUF_PRIMED ; 
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qeth_fill_buffer (struct qeth_qdio_out_q*,struct qeth_qdio_out_buffer*,struct sk_buff*,struct qeth_hdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_flush_buffers (struct qeth_qdio_out_q*,int,int) ; 
 scalar_t__ qeth_flush_buffers_on_no_pci (struct qeth_qdio_out_q*) ; 
 scalar_t__ qeth_switch_to_nonpacking_if_needed (struct qeth_qdio_out_q*) ; 
 int /*<<< orphan*/  qeth_switch_to_packing_if_needed (struct qeth_qdio_out_q*) ; 

int qeth_do_send_packet(struct qeth_card *card, struct qeth_qdio_out_q *queue,
		struct sk_buff *skb, struct qeth_hdr *hdr,
		int elements_needed)
{
	struct qeth_qdio_out_buffer *buffer;
	int start_index;
	int flush_count = 0;
	int do_pack = 0;
	int tmp;
	int rc = 0;

	/* spin until we get the queue ... */
	while (atomic_cmpxchg(&queue->state, QETH_OUT_Q_UNLOCKED,
			      QETH_OUT_Q_LOCKED) != QETH_OUT_Q_UNLOCKED);
	start_index = queue->next_buf_to_fill;
	buffer = queue->bufs[queue->next_buf_to_fill];
	/*
	 * check if buffer is empty to make sure that we do not 'overtake'
	 * ourselves and try to fill a buffer that is already primed
	 */
	if (atomic_read(&buffer->state) != QETH_QDIO_BUF_EMPTY) {
		atomic_set(&queue->state, QETH_OUT_Q_UNLOCKED);
		return -EBUSY;
	}
	/* check if we need to switch packing state of this queue */
	qeth_switch_to_packing_if_needed(queue);
	if (queue->do_pack) {
		do_pack = 1;
		/* does packet fit in current buffer? */
		if ((QETH_MAX_BUFFER_ELEMENTS(card) -
		    buffer->next_element_to_fill) < elements_needed) {
			/* ... no -> set state PRIMED */
			atomic_set(&buffer->state, QETH_QDIO_BUF_PRIMED);
			flush_count++;
			queue->next_buf_to_fill =
				(queue->next_buf_to_fill + 1) %
				QDIO_MAX_BUFFERS_PER_Q;
			buffer = queue->bufs[queue->next_buf_to_fill];
			/* we did a step forward, so check buffer state
			 * again */
			if (atomic_read(&buffer->state) !=
			    QETH_QDIO_BUF_EMPTY) {
				qeth_flush_buffers(queue, start_index,
							   flush_count);
				atomic_set(&queue->state,
						QETH_OUT_Q_UNLOCKED);
				return -EBUSY;
			}
		}
	}
	tmp = qeth_fill_buffer(queue, buffer, skb, hdr, -1, 0);
	queue->next_buf_to_fill = (queue->next_buf_to_fill + tmp) %
				  QDIO_MAX_BUFFERS_PER_Q;
	flush_count += tmp;
	if (flush_count)
		qeth_flush_buffers(queue, start_index, flush_count);
	else if (!atomic_read(&queue->set_pci_flags_count))
		atomic_xchg(&queue->state, QETH_OUT_Q_LOCKED_FLUSH);
	/*
	 * queue->state will go from LOCKED -> UNLOCKED or from
	 * LOCKED_FLUSH -> LOCKED if output_handler wanted to 'notify' us
	 * (switch packing state or flush buffer to get another pci flag out).
	 * In that case we will enter this loop
	 */
	while (atomic_dec_return(&queue->state)) {
		flush_count = 0;
		start_index = queue->next_buf_to_fill;
		/* check if we can go back to non-packing state */
		flush_count += qeth_switch_to_nonpacking_if_needed(queue);
		/*
		 * check if we need to flush a packing buffer to get a pci
		 * flag out on the queue
		 */
		if (!flush_count && !atomic_read(&queue->set_pci_flags_count))
			flush_count += qeth_flush_buffers_on_no_pci(queue);
		if (flush_count)
			qeth_flush_buffers(queue, start_index, flush_count);
	}
	/* at this point the queue is UNLOCKED again */
	if (queue->card->options.performance_stats && do_pack)
		queue->card->perf_stats.bufs_sent_pack += flush_count;

	return rc;
}