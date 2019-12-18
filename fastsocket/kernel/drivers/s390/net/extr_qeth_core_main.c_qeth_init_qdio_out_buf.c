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
struct qeth_qdio_out_q {TYPE_1__* bufstates; struct qeth_qdio_out_buffer** bufs; int /*<<< orphan*/ * qdio_bufs; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct qeth_qdio_out_buffer {int /*<<< orphan*/  state; struct qeth_qdio_out_buffer* next_pending; int /*<<< orphan*/ * aob; struct qeth_qdio_out_q* q; TYPE_2__ skb_list; int /*<<< orphan*/ * buffer; } ;
struct TYPE_3__ {struct qeth_qdio_out_buffer* user; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  QETH_QDIO_BUF_EMPTY ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qeth_qdio_out_buffer* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdio_out_skb_queue_key ; 
 int /*<<< orphan*/  qeth_qdio_outbuf_cache ; 
 int /*<<< orphan*/  skb_queue_head_init (TYPE_2__*) ; 

__attribute__((used)) static int qeth_init_qdio_out_buf(struct qeth_qdio_out_q *q, int bidx)
{
	int rc;
	struct qeth_qdio_out_buffer *newbuf;

	rc = 0;
	newbuf = kmem_cache_zalloc(qeth_qdio_outbuf_cache, GFP_ATOMIC);
	if (!newbuf) {
		rc = -ENOMEM;
		goto out;
	}
	newbuf->buffer = &q->qdio_bufs[bidx];
	skb_queue_head_init(&newbuf->skb_list);
	lockdep_set_class(&newbuf->skb_list.lock, &qdio_out_skb_queue_key);
	newbuf->q = q;
	newbuf->aob = NULL;
	newbuf->next_pending = q->bufs[bidx];
	atomic_set(&newbuf->state, QETH_QDIO_BUF_EMPTY);
	q->bufs[bidx] = newbuf;
	if (q->bufstates) {
		q->bufstates[bidx].user = newbuf;
	}
out:
	return rc;
}