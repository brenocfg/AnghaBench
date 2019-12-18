#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dma_chan {int dummy; } ;
struct at_dma_chan {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atc_advance_work (struct at_dma_chan*) ; 
 int /*<<< orphan*/  atc_chan_is_enabled (struct at_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct at_dma_chan* to_at_dma_chan (struct dma_chan*) ; 

__attribute__((used)) static void atc_issue_pending(struct dma_chan *chan)
{
	struct at_dma_chan	*atchan = to_at_dma_chan(chan);

	dev_vdbg(chan2dev(chan), "issue_pending\n");

	if (!atc_chan_is_enabled(atchan)) {
		spin_lock_bh(&atchan->lock);
		atc_advance_work(atchan);
		spin_unlock_bh(&atchan->lock);
	}
}