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
struct qeth_qdio_out_q {size_t next_buf_to_fill; struct qeth_qdio_out_buffer** bufs; scalar_t__ do_pack; TYPE_3__* card; int /*<<< orphan*/  used_buffers; } ;
struct qeth_qdio_out_buffer {scalar_t__ next_element_to_fill; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {int /*<<< orphan*/  sc_p_dp; } ;
struct TYPE_4__ {scalar_t__ performance_stats; } ;
struct TYPE_6__ {TYPE_2__ perf_stats; TYPE_1__ options; } ;

/* Variables and functions */
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ QETH_LOW_WATERMARK_PACK ; 
 scalar_t__ QETH_QDIO_BUF_EMPTY ; 
 int /*<<< orphan*/  QETH_QDIO_BUF_PRIMED ; 
 int /*<<< orphan*/  TRACE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_switch_to_nonpacking_if_needed(struct qeth_qdio_out_q *queue)
{
	struct qeth_qdio_out_buffer *buffer;
	int flush_count = 0;

	if (queue->do_pack) {
		if (atomic_read(&queue->used_buffers)
		    <= QETH_LOW_WATERMARK_PACK) {
			/* switch PACKING -> non-PACKING */
			QETH_DBF_TEXT(TRACE, 6, "pack->np");
			if (queue->card->options.performance_stats)
				queue->card->perf_stats.sc_p_dp++;
			queue->do_pack = 0;
			/* flush packing buffers */
			buffer = queue->bufs[queue->next_buf_to_fill];
			if ((atomic_read(&buffer->state) ==
						QETH_QDIO_BUF_EMPTY) &&
			    (buffer->next_element_to_fill > 0)) {
				atomic_set(&buffer->state,
					   QETH_QDIO_BUF_PRIMED);
				flush_count++;
				queue->next_buf_to_fill =
					(queue->next_buf_to_fill + 1) %
					QDIO_MAX_BUFFERS_PER_Q;
			}
		}
	}
	return flush_count;
}