#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_8__ {scalar_t__ sw_q_depth; int /*<<< orphan*/  hw_q_depth; } ;
struct TYPE_7__ {size_t idx; struct hw_status* buf; } ;
struct rsxx_dma_ctrl {scalar_t__ e_cnt; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  issue_dma_work; int /*<<< orphan*/  issue_wq; TYPE_2__ stats; TYPE_3__* card; int /*<<< orphan*/  id; int /*<<< orphan*/  activity_timer; TYPE_1__ status; int /*<<< orphan*/  trackers; } ;
struct rsxx_dma {int /*<<< orphan*/  laddr; } ;
struct hw_status {int /*<<< orphan*/  count; scalar_t__ tag; scalar_t__ status; } ;
struct TYPE_9__ {int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  eeh_state; int /*<<< orphan*/  dma_fault; int /*<<< orphan*/  halt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (TYPE_3__*) ; 
 int /*<<< orphan*/  CR_INTR_DMA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CR_INTR_DMA_ALL ; 
 scalar_t__ DMA_ACTIVITY_TIMEOUT ; 
 int RSXX_CS_IDX_MASK ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_intr_coal_auto_tune (TYPE_3__*) ; 
 struct rsxx_dma* get_tracker_dma (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ jiffies ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  push_tracker (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  rsxx_complete_dma (struct rsxx_dma_ctrl*,struct rsxx_dma*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_disable_ier (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_enable_ier (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_handle_dma_error (struct rsxx_dma_ctrl*,struct rsxx_dma*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rsxx_dma_done(struct rsxx_dma_ctrl *ctrl)
{
	struct rsxx_dma *dma;
	unsigned long flags;
	u16 count;
	u8 status;
	u8 tag;
	struct hw_status *hw_st_buf;

	hw_st_buf = ctrl->status.buf;

	if (unlikely(ctrl->card->halt) ||
	    unlikely(ctrl->card->dma_fault) ||
	    unlikely(ctrl->card->eeh_state))
		return;

	count = le16_to_cpu(hw_st_buf[ctrl->status.idx].count);

	while (count == ctrl->e_cnt) {
		/*
		 * The read memory-barrier is necessary to keep aggressive
		 * processors/optimizers (such as the PPC Apple G5) from
		 * reordering the following status-buffer tag & status read
		 * *before* the count read on subsequent iterations of the
		 * loop!
		 */
		rmb();

		status = hw_st_buf[ctrl->status.idx].status;
		tag    = hw_st_buf[ctrl->status.idx].tag;

		dma = get_tracker_dma(ctrl->trackers, tag);
		if (dma == NULL) {
			spin_lock_irqsave(&ctrl->card->irq_lock, flags);
			rsxx_disable_ier(ctrl->card, CR_INTR_DMA_ALL);
			spin_unlock_irqrestore(&ctrl->card->irq_lock, flags);

			dev_err(CARD_TO_DEV(ctrl->card),
				"No tracker for tag %d "
				"(idx %d id %d)\n",
				tag, ctrl->status.idx, ctrl->id);
			return;
		}

		dev_dbg(CARD_TO_DEV(ctrl->card),
			"Completing DMA%d"
			"(laddr x%x tag %d st: x%x cnt: x%04x) from idx %d.\n",
			ctrl->id, dma->laddr, tag, status, count,
			ctrl->status.idx);

		atomic_dec(&ctrl->stats.hw_q_depth);

		mod_timer(&ctrl->activity_timer,
			  jiffies + DMA_ACTIVITY_TIMEOUT);

		if (status)
			rsxx_handle_dma_error(ctrl, dma, status);
		else
			rsxx_complete_dma(ctrl, dma, 0);

		push_tracker(ctrl->trackers, tag);

		ctrl->status.idx = (ctrl->status.idx + 1) &
				   RSXX_CS_IDX_MASK;
		ctrl->e_cnt++;

		count = le16_to_cpu(hw_st_buf[ctrl->status.idx].count);
	}

	dma_intr_coal_auto_tune(ctrl->card);

	if (atomic_read(&ctrl->stats.hw_q_depth) == 0)
		del_timer_sync(&ctrl->activity_timer);

	spin_lock_irqsave(&ctrl->card->irq_lock, flags);
	rsxx_enable_ier(ctrl->card, CR_INTR_DMA(ctrl->id));
	spin_unlock_irqrestore(&ctrl->card->irq_lock, flags);

	spin_lock_bh(&ctrl->queue_lock);
	if (ctrl->stats.sw_q_depth)
		queue_work(ctrl->issue_wq, &ctrl->issue_dma_work);
	spin_unlock_bh(&ctrl->queue_lock);
}