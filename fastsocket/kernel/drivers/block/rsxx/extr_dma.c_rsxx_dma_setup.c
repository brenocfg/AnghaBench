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
struct TYPE_4__ {int /*<<< orphan*/  dma_addr; scalar_t__ buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_addr; scalar_t__ buf; } ;
struct rsxx_dma_ctrl {int id; TYPE_2__ cmd; TYPE_1__ status; scalar_t__ trackers; int /*<<< orphan*/ * done_wq; int /*<<< orphan*/ * issue_wq; struct rsxx_cardinfo* card; scalar_t__ regmap; } ;
struct rsxx_cardinfo {int n_targets; int scrub_hard; int /*<<< orphan*/  dev; struct rsxx_dma_ctrl* ctrl; int /*<<< orphan*/  irq_lock; scalar_t__ config_valid; scalar_t__ dma_fault; scalar_t__ regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  COMMAND_BUFFER_SIZE8 ; 
 int /*<<< orphan*/  CR_INTR_DMA (int) ; 
 int /*<<< orphan*/  STATUS_BUFFER_SIZE8 ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsxx_dma_configure (struct rsxx_cardinfo*) ; 
 int rsxx_dma_ctrl_init (int /*<<< orphan*/ ,struct rsxx_dma_ctrl*) ; 
 int /*<<< orphan*/  rsxx_dma_queue_reset (struct rsxx_cardinfo*) ; 
 int /*<<< orphan*/  rsxx_enable_ier_and_isr (struct rsxx_cardinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vfree (scalar_t__) ; 

int rsxx_dma_setup(struct rsxx_cardinfo *card)
{
	unsigned long flags;
	int st;
	int i;

	dev_info(CARD_TO_DEV(card),
		"Initializing %d DMA targets\n",
		card->n_targets);

	/* Regmap is divided up into 4K chunks. One for each DMA channel */
	for (i = 0; i < card->n_targets; i++)
		card->ctrl[i].regmap = card->regmap + (i * 4096);

	card->dma_fault = 0;

	/* Reset the DMA queues */
	rsxx_dma_queue_reset(card);

	/************* Setup DMA Control *************/
	for (i = 0; i < card->n_targets; i++) {
		st = rsxx_dma_ctrl_init(card->dev, &card->ctrl[i]);
		if (st)
			goto failed_dma_setup;

		card->ctrl[i].card = card;
		card->ctrl[i].id = i;
	}

	card->scrub_hard = 1;

	if (card->config_valid)
		rsxx_dma_configure(card);

	/* Enable the interrupts after all setup has completed. */
	for (i = 0; i < card->n_targets; i++) {
		spin_lock_irqsave(&card->irq_lock, flags);
		rsxx_enable_ier_and_isr(card, CR_INTR_DMA(i));
		spin_unlock_irqrestore(&card->irq_lock, flags);
	}

	return 0;

failed_dma_setup:
	for (i = 0; i < card->n_targets; i++) {
		struct rsxx_dma_ctrl *ctrl = &card->ctrl[i];

		if (ctrl->issue_wq) {
			destroy_workqueue(ctrl->issue_wq);
			ctrl->issue_wq = NULL;
		}

		if (ctrl->done_wq) {
			destroy_workqueue(ctrl->done_wq);
			ctrl->done_wq = NULL;
		}

		if (ctrl->trackers)
			vfree(ctrl->trackers);

		if (ctrl->status.buf)
			pci_free_consistent(card->dev, STATUS_BUFFER_SIZE8,
					    ctrl->status.buf,
					    ctrl->status.dma_addr);
		if (ctrl->cmd.buf)
			pci_free_consistent(card->dev, COMMAND_BUFFER_SIZE8,
					    ctrl->cmd.buf, ctrl->cmd.dma_addr);
	}

	return st;
}