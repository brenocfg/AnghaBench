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
struct at_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  error_status; int /*<<< orphan*/  chan_common; } ;

/* Variables and functions */
 int /*<<< orphan*/  atc_advance_work (struct at_dma_chan*) ; 
 scalar_t__ atc_chan_is_enabled (struct at_dma_chan*) ; 
 int /*<<< orphan*/  atc_handle_error (struct at_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atc_tasklet(unsigned long data)
{
	struct at_dma_chan *atchan = (struct at_dma_chan *)data;

	/* Channel cannot be enabled here */
	if (atc_chan_is_enabled(atchan)) {
		dev_err(chan2dev(&atchan->chan_common),
			"BUG: channel enabled in tasklet\n");
		return;
	}

	spin_lock(&atchan->lock);
	if (test_and_clear_bit(0, &atchan->error_status))
		atc_handle_error(atchan);
	else
		atc_advance_work(atchan);

	spin_unlock(&atchan->lock);
}