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
struct wl1251 {scalar_t__ state; int next_tx_complete; int tx_queue_stopped; TYPE_1__* data_path; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  tx_queue; } ;
struct tx_result {int done_1; int done_2; } ;
typedef  int /*<<< orphan*/  result ;
struct TYPE_2__ {scalar_t__ tx_complete_addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct tx_result*) ; 
 int /*<<< orphan*/  DEBUG_TX ; 
 int FW_TX_CMPLT_BLOCK_SIZE ; 
 scalar_t__ WL1251_STATE_ON ; 
 int WL1251_TX_QUEUE_LOW_WATERMARK ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_wake_queues (int /*<<< orphan*/ ) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_mem_read (struct wl1251*,scalar_t__,struct tx_result*,int) ; 
 int /*<<< orphan*/  wl1251_mem_write (struct wl1251*,scalar_t__,struct tx_result*,int) ; 
 int /*<<< orphan*/  wl1251_tx_packet_cb (struct wl1251*,struct tx_result*) ; 

void wl1251_tx_complete(struct wl1251 *wl)
{
	int i, result_index, num_complete = 0, queue_len;
	struct tx_result result[FW_TX_CMPLT_BLOCK_SIZE], *result_ptr;
	unsigned long flags;

	if (unlikely(wl->state != WL1251_STATE_ON))
		return;

	/* First we read the result */
	wl1251_mem_read(wl, wl->data_path->tx_complete_addr,
			    result, sizeof(result));

	result_index = wl->next_tx_complete;

	for (i = 0; i < ARRAY_SIZE(result); i++) {
		result_ptr = &result[result_index];

		if (result_ptr->done_1 == 1 &&
		    result_ptr->done_2 == 1) {
			wl1251_tx_packet_cb(wl, result_ptr);

			result_ptr->done_1 = 0;
			result_ptr->done_2 = 0;

			result_index = (result_index + 1) &
				(FW_TX_CMPLT_BLOCK_SIZE - 1);
			num_complete++;
		} else {
			break;
		}
	}

	queue_len = skb_queue_len(&wl->tx_queue);

	if ((num_complete > 0) && (queue_len > 0)) {
		/* firmware buffer has space, reschedule tx_work */
		wl1251_debug(DEBUG_TX, "tx_complete: reschedule tx_work");
		ieee80211_queue_work(wl->hw, &wl->tx_work);
	}

	if (wl->tx_queue_stopped &&
	    queue_len <= WL1251_TX_QUEUE_LOW_WATERMARK) {
		/* tx_queue has space, restart queues */
		wl1251_debug(DEBUG_TX, "tx_complete: waking queues");
		spin_lock_irqsave(&wl->wl_lock, flags);
		ieee80211_wake_queues(wl->hw);
		wl->tx_queue_stopped = false;
		spin_unlock_irqrestore(&wl->wl_lock, flags);
	}

	/* Every completed frame needs to be acknowledged */
	if (num_complete) {
		/*
		 * If we've wrapped, we have to clear
		 * the results in 2 steps.
		 */
		if (result_index > wl->next_tx_complete) {
			/* Only 1 write is needed */
			wl1251_mem_write(wl,
					 wl->data_path->tx_complete_addr +
					 (wl->next_tx_complete *
					  sizeof(struct tx_result)),
					 &result[wl->next_tx_complete],
					 num_complete *
					 sizeof(struct tx_result));


		} else if (result_index < wl->next_tx_complete) {
			/* 2 writes are needed */
			wl1251_mem_write(wl,
					 wl->data_path->tx_complete_addr +
					 (wl->next_tx_complete *
					  sizeof(struct tx_result)),
					 &result[wl->next_tx_complete],
					 (FW_TX_CMPLT_BLOCK_SIZE -
					  wl->next_tx_complete) *
					 sizeof(struct tx_result));

			wl1251_mem_write(wl,
					 wl->data_path->tx_complete_addr,
					 result,
					 (num_complete -
					  FW_TX_CMPLT_BLOCK_SIZE +
					  wl->next_tx_complete) *
					 sizeof(struct tx_result));

		} else {
			/* We have to write the whole array */
			wl1251_mem_write(wl,
					 wl->data_path->tx_complete_addr,
					 result,
					 FW_TX_CMPLT_BLOCK_SIZE *
					 sizeof(struct tx_result));
		}

	}

	wl->next_tx_complete = result_index;
}