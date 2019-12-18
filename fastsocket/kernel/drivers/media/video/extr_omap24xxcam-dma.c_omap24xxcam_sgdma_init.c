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
struct omap24xxcam_sgdma {int free_sgdma; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  dma; TYPE_1__* sg_state; scalar_t__ next_sgdma; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * arg; int /*<<< orphan*/ * callback; scalar_t__ csr; scalar_t__ queued_sglist; scalar_t__ bytes_read; scalar_t__ next_sglist; scalar_t__ sglen; } ;

/* Variables and functions */
 int NUM_SG_DMA ; 
 int /*<<< orphan*/  omap24xxcam_dma_init (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void omap24xxcam_sgdma_init(struct omap24xxcam_sgdma *sgdma,
			    unsigned long base,
			    void (*reset_callback)(unsigned long data),
			    unsigned long reset_callback_data)
{
	int sg;

	spin_lock_init(&sgdma->lock);
	sgdma->free_sgdma = NUM_SG_DMA;
	sgdma->next_sgdma = 0;
	for (sg = 0; sg < NUM_SG_DMA; sg++) {
		sgdma->sg_state[sg].sglen = 0;
		sgdma->sg_state[sg].next_sglist = 0;
		sgdma->sg_state[sg].bytes_read = 0;
		sgdma->sg_state[sg].queued_sglist = 0;
		sgdma->sg_state[sg].csr = 0;
		sgdma->sg_state[sg].callback = NULL;
		sgdma->sg_state[sg].arg = NULL;
	}

	omap24xxcam_dma_init(&sgdma->dma, base);
	setup_timer(&sgdma->reset_timer, reset_callback, reset_callback_data);
}