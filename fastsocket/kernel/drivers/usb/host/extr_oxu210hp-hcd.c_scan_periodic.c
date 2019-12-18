#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
union ehci_shadow {int /*<<< orphan*/ * ptr; TYPE_2__* qh; } ;
struct oxu_hcd {int periodic_size; unsigned int next_uframe; int* periodic; TYPE_1__* regs; union ehci_shadow* pshadow; } ;
typedef  int __le32 ;
struct TYPE_10__ {int /*<<< orphan*/  state; } ;
struct TYPE_9__ {int hw_next; int /*<<< orphan*/  qtd_list; union ehci_shadow qh_next; } ;
struct TYPE_8__ {int /*<<< orphan*/  frame_index; } ;

/* Variables and functions */
 int HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int Q_NEXT_TYPE (int) ; 
#define  Q_TYPE_QH 128 
 int /*<<< orphan*/  dbg (char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr_deschedule (struct oxu_hcd*,TYPE_2__*) ; 
 unsigned int list_empty (int /*<<< orphan*/ *) ; 
 TYPE_6__* oxu_to_hcd (struct oxu_hcd*) ; 
 unsigned int qh_completions (struct oxu_hcd*,TYPE_2__*) ; 
 TYPE_2__* qh_get (TYPE_2__*) ; 
 int /*<<< orphan*/  qh_put (TYPE_2__*) ; 
 unsigned int readl (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static void scan_periodic(struct oxu_hcd *oxu)
{
	unsigned frame, clock, now_uframe, mod;
	unsigned modified;

	mod = oxu->periodic_size << 3;

	/*
	 * When running, scan from last scan point up to "now"
	 * else clean up by scanning everything that's left.
	 * Touches as few pages as possible:  cache-friendly.
	 */
	now_uframe = oxu->next_uframe;
	if (HC_IS_RUNNING(oxu_to_hcd(oxu)->state))
		clock = readl(&oxu->regs->frame_index);
	else
		clock = now_uframe + mod - 1;
	clock %= mod;

	for (;;) {
		union ehci_shadow	q, *q_p;
		__le32			type, *hw_p;
		unsigned		uframes;

		/* don't scan past the live uframe */
		frame = now_uframe >> 3;
		if (frame == (clock >> 3))
			uframes = now_uframe & 0x07;
		else {
			/* safe to scan the whole frame at once */
			now_uframe |= 0x07;
			uframes = 8;
		}

restart:
		/* scan each element in frame's queue for completions */
		q_p = &oxu->pshadow[frame];
		hw_p = &oxu->periodic[frame];
		q.ptr = q_p->ptr;
		type = Q_NEXT_TYPE(*hw_p);
		modified = 0;

		while (q.ptr != NULL) {
			union ehci_shadow temp;
			int live;

			live = HC_IS_RUNNING(oxu_to_hcd(oxu)->state);
			switch (type) {
			case Q_TYPE_QH:
				/* handle any completions */
				temp.qh = qh_get(q.qh);
				type = Q_NEXT_TYPE(q.qh->hw_next);
				q = q.qh->qh_next;
				modified = qh_completions(oxu, temp.qh);
				if (unlikely(list_empty(&temp.qh->qtd_list)))
					intr_deschedule(oxu, temp.qh);
				qh_put(temp.qh);
				break;
			default:
				dbg("corrupt type %d frame %d shadow %p",
					type, frame, q.ptr);
				q.ptr = NULL;
			}

			/* assume completion callbacks modify the queue */
			if (unlikely(modified))
				goto restart;
		}

		/* Stop when we catch up to the HC */

		/* FIXME:  this assumes we won't get lapped when
		 * latencies climb; that should be rare, but...
		 * detect it, and just go all the way around.
		 * FLR might help detect this case, so long as latencies
		 * don't exceed periodic_size msec (default 1.024 sec).
		 */

		/* FIXME: likewise assumes HC doesn't halt mid-scan */

		if (now_uframe == clock) {
			unsigned	now;

			if (!HC_IS_RUNNING(oxu_to_hcd(oxu)->state))
				break;
			oxu->next_uframe = now_uframe;
			now = readl(&oxu->regs->frame_index) % mod;
			if (now_uframe == now)
				break;

			/* rescan the rest of this frame, then ... */
			clock = now;
		} else {
			now_uframe++;
			now_uframe %= mod;
		}
	}
}