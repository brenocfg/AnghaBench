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
struct at_dma_chan {int /*<<< orphan*/  active_list; int /*<<< orphan*/  chan_common; } ;

/* Variables and functions */
 int /*<<< orphan*/  atc_chain_complete (struct at_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atc_complete_all (struct at_dma_chan*) ; 
 int /*<<< orphan*/  atc_dostart (struct at_dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atc_first_active (struct at_dma_chan*) ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ list_is_singular (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atc_advance_work(struct at_dma_chan *atchan)
{
	dev_vdbg(chan2dev(&atchan->chan_common), "advance_work\n");

	if (list_empty(&atchan->active_list) ||
	    list_is_singular(&atchan->active_list)) {
		atc_complete_all(atchan);
	} else {
		atc_chain_complete(atchan, atc_first_active(atchan));
		/* advance work */
		atc_dostart(atchan, atc_first_active(atchan));
	}
}