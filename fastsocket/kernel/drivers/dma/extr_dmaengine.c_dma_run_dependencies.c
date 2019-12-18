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
struct dma_chan {TYPE_1__* device; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  (* tx_submit ) (struct dma_async_tx_descriptor*) ;int /*<<< orphan*/  lock; struct dma_async_tx_descriptor* next; struct dma_chan* chan; int /*<<< orphan*/ * parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* device_issue_pending ) (struct dma_chan*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  stub2 (struct dma_chan*) ; 

void dma_run_dependencies(struct dma_async_tx_descriptor *tx)
{
	struct dma_async_tx_descriptor *dep = tx->next;
	struct dma_async_tx_descriptor *dep_next;
	struct dma_chan *chan;

	if (!dep)
		return;

	/* we'll submit tx->next now, so clear the link */
	tx->next = NULL;
	chan = dep->chan;

	/* keep submitting up until a channel switch is detected
	 * in that case we will be called again as a result of
	 * processing the interrupt from async_tx_channel_switch
	 */
	for (; dep; dep = dep_next) {
		spin_lock_bh(&dep->lock);
		dep->parent = NULL;
		dep_next = dep->next;
		if (dep_next && dep_next->chan == chan)
			dep->next = NULL; /* ->next will be submitted */
		else
			dep_next = NULL; /* submit current dep and terminate */
		spin_unlock_bh(&dep->lock);

		dep->tx_submit(dep);
	}

	chan->device->device_issue_pending(chan);
}