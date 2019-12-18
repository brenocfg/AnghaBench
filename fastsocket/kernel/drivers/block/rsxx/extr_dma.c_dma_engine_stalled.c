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
struct TYPE_5__ {scalar_t__ idx; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_q_depth; } ;
struct rsxx_dma_ctrl {int /*<<< orphan*/  id; TYPE_3__* card; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  activity_timer; scalar_t__ regmap; TYPE_2__ cmd; TYPE_1__ stats; } ;
struct TYPE_6__ {int dma_fault; int /*<<< orphan*/  eeh_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (TYPE_3__*) ; 
 int /*<<< orphan*/  COMPLETE_DMA ; 
 scalar_t__ DMA_ACTIVITY_TIMEOUT ; 
 scalar_t__ SW_CMD_IDX ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int rsxx_cleanup_dma_queue (struct rsxx_dma_ctrl*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rsxx_dma_cancel (struct rsxx_dma_ctrl*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_engine_stalled(unsigned long data)
{
	struct rsxx_dma_ctrl *ctrl = (struct rsxx_dma_ctrl *)data;
	int cnt;

	if (atomic_read(&ctrl->stats.hw_q_depth) == 0 ||
	    unlikely(ctrl->card->eeh_state))
		return;

	if (ctrl->cmd.idx != ioread32(ctrl->regmap + SW_CMD_IDX)) {
		/*
		 * The dma engine was stalled because the SW_CMD_IDX write
		 * was lost. Issue it again to recover.
		 */
		dev_warn(CARD_TO_DEV(ctrl->card),
			"SW_CMD_IDX write was lost, re-writing...\n");
		iowrite32(ctrl->cmd.idx, ctrl->regmap + SW_CMD_IDX);
		mod_timer(&ctrl->activity_timer,
			  jiffies + DMA_ACTIVITY_TIMEOUT);
	} else {
		dev_warn(CARD_TO_DEV(ctrl->card),
			"DMA channel %d has stalled, faulting interface.\n",
			ctrl->id);
		ctrl->card->dma_fault = 1;

		/* Clean up the DMA queue */
		spin_lock(&ctrl->queue_lock);
		cnt = rsxx_cleanup_dma_queue(ctrl, &ctrl->queue, COMPLETE_DMA);
		spin_unlock(&ctrl->queue_lock);

		cnt += rsxx_dma_cancel(ctrl);

		if (cnt)
			dev_info(CARD_TO_DEV(ctrl->card),
				"Freed %d queued DMAs on channel %d\n",
				cnt, ctrl->id);
	}
}