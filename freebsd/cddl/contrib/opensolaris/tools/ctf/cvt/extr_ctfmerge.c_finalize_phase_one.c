#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int wq_nwipslots; scalar_t__ wq_lastdonebatch; int /*<<< orphan*/  wq_donequeue; int /*<<< orphan*/  wq_next_batchid; TYPE_2__* wq_wip; } ;
typedef  TYPE_1__ workqueue_t ;
struct TYPE_5__ {scalar_t__ wip_batchid; int /*<<< orphan*/ * wip_td; int /*<<< orphan*/  wip_nmerged; } ;
typedef  TYPE_2__ wip_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug (int,char*,int,...) ; 
 int /*<<< orphan*/  fifo_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fifo_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
finalize_phase_one(workqueue_t *wq)
{
	int startslot, i;

	/*
	 * wip slots are cleared out only when maxbatchsz td's have been merged
	 * into them.  We're not guaranteed that the number of files we're
	 * merging is a multiple of maxbatchsz, so there will be some partial
	 * groups in the wip array.  Move them to the done queue in batch ID
	 * order, starting with the slot containing the next batch that would
	 * have been placed on the done queue, followed by the others.
	 * One thread will be doing this while the others wait at the barrier
	 * back in worker_thread(), so we don't need to worry about pesky things
	 * like locks.
	 */

	for (startslot = -1, i = 0; i < wq->wq_nwipslots; i++) {
		if (wq->wq_wip[i].wip_batchid == wq->wq_lastdonebatch + 1) {
			startslot = i;
			break;
		}
	}

	assert(startslot != -1);

	for (i = startslot; i < startslot + wq->wq_nwipslots; i++) {
		int slotnum = i % wq->wq_nwipslots;
		wip_t *wipslot = &wq->wq_wip[slotnum];

		if (wipslot->wip_td != NULL) {
			debug(2, "clearing slot %d (%d) (saving %d)\n",
			    slotnum, i, wipslot->wip_nmerged);
		} else
			debug(2, "clearing slot %d (%d)\n", slotnum, i);

		if (wipslot->wip_td != NULL) {
			fifo_add(wq->wq_donequeue, wipslot->wip_td);
			wq->wq_wip[slotnum].wip_td = NULL;
		}
	}

	wq->wq_lastdonebatch = wq->wq_next_batchid++;

	debug(2, "phase one done: donequeue has %d items\n",
	    fifo_len(wq->wq_donequeue));
}