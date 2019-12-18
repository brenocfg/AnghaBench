#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipw_rx_queue {scalar_t__ free_count; scalar_t__ write; scalar_t__ read; int /*<<< orphan*/  rx_used; TYPE_1__* pool; int /*<<< orphan*/  rx_free; int /*<<< orphan*/  lock; } ;
struct ipw_priv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPW_ERROR (char*) ; 
 int RX_FREE_BUFFERS ; 
 int RX_QUEUE_SIZE ; 
 struct ipw_rx_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ipw_rx_queue *ipw_rx_queue_alloc(struct ipw_priv *priv)
{
	struct ipw_rx_queue *rxq;
	int i;

	rxq = kzalloc(sizeof(*rxq), GFP_KERNEL);
	if (unlikely(!rxq)) {
		IPW_ERROR("memory allocation failed\n");
		return NULL;
	}
	spin_lock_init(&rxq->lock);
	INIT_LIST_HEAD(&rxq->rx_free);
	INIT_LIST_HEAD(&rxq->rx_used);

	/* Fill the rx_used queue with _all_ of the Rx buffers */
	for (i = 0; i < RX_FREE_BUFFERS + RX_QUEUE_SIZE; i++)
		list_add_tail(&rxq->pool[i].list, &rxq->rx_used);

	/* Set us so that we have processed and used all buffers, but have
	 * not restocked the Rx queue with fresh buffers */
	rxq->read = rxq->write = 0;
	rxq->free_count = 0;

	return rxq;
}