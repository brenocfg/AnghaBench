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
struct qeth_qdio_buffer {TYPE_3__* buffer; struct qeth_buffer_pool_entry* pool_entry; scalar_t__ rx_skb; } ;
struct TYPE_4__ {scalar_t__ cq; } ;
struct qeth_card {TYPE_1__ options; } ;
struct qeth_buffer_pool_entry {int /*<<< orphan*/ * elements; } ;
struct TYPE_6__ {TYPE_2__* element; } ;
struct TYPE_5__ {scalar_t__ sflags; scalar_t__ eflags; int /*<<< orphan*/  addr; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ QETH_CQ_ENABLED ; 
 int QETH_MAX_BUFFER_ELEMENTS (struct qeth_card*) ; 
 scalar_t__ QETH_RX_PULL_LEN ; 
 scalar_t__ SBAL_EFLAGS_LAST_ENTRY ; 
 scalar_t__ dev_alloc_skb (scalar_t__) ; 
 struct qeth_buffer_pool_entry* qeth_find_free_buffer_pool_entry (struct qeth_card*) ; 

__attribute__((used)) static int qeth_init_input_buffer(struct qeth_card *card,
		struct qeth_qdio_buffer *buf)
{
	struct qeth_buffer_pool_entry *pool_entry;
	int i;

	if ((card->options.cq == QETH_CQ_ENABLED) && (!buf->rx_skb)) {
		buf->rx_skb = dev_alloc_skb(QETH_RX_PULL_LEN + ETH_HLEN);
		if (!buf->rx_skb)
			return 1;
	}

	pool_entry = qeth_find_free_buffer_pool_entry(card);
	if (!pool_entry)
		return 1;

	/*
	 * since the buffer is accessed only from the input_tasklet
	 * there shouldn't be a need to synchronize; also, since we use
	 * the QETH_IN_BUF_REQUEUE_THRESHOLD we should never run  out off
	 * buffers
	 */

	buf->pool_entry = pool_entry;
	for (i = 0; i < QETH_MAX_BUFFER_ELEMENTS(card); ++i) {
		buf->buffer->element[i].length = PAGE_SIZE;
		buf->buffer->element[i].addr =  pool_entry->elements[i];
		if (i == QETH_MAX_BUFFER_ELEMENTS(card) - 1)
			buf->buffer->element[i].eflags = SBAL_EFLAGS_LAST_ENTRY;
		else
			buf->buffer->element[i].eflags = 0;
		buf->buffer->element[i].sflags = 0;
	}
	return 0;
}