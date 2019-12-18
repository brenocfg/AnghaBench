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
typedef  int u32 ;
struct ehci_iso_stream {int raw_mask; int usecs; int c_usecs; int /*<<< orphan*/  splits; int /*<<< orphan*/  udev; int /*<<< orphan*/  tt_usecs; } ;
struct ehci_iso_sched {int dummy; } ;
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_hc32 (struct ehci_hcd*,int) ; 
 int periodic_usecs (struct ehci_hcd*,int,int) ; 
 int /*<<< orphan*/  tt_available (struct ehci_hcd*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tt_no_collision (struct ehci_hcd*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int
sitd_slot_ok (
	struct ehci_hcd		*ehci,
	u32			mod,
	struct ehci_iso_stream	*stream,
	u32			uframe,
	struct ehci_iso_sched	*sched,
	u32			period_uframes
)
{
	u32			mask, tmp;
	u32			frame, uf;

	mask = stream->raw_mask << (uframe & 7);

	/* for IN, don't wrap CSPLIT into the next frame */
	if (mask & ~0xffff)
		return 0;

	/* this multi-pass logic is simple, but performance may
	 * suffer when the schedule data isn't cached.
	 */

	/* check bandwidth */
	uframe %= period_uframes;
	do {
		u32		max_used;

		frame = uframe >> 3;
		uf = uframe & 7;

#ifdef CONFIG_USB_EHCI_TT_NEWSCHED
		/* The tt's fullspeed bus bandwidth must be available.
		 * tt_available scheduling guarantees 10+% for control/bulk.
		 */
		if (!tt_available (ehci, period_uframes << 3,
				stream->udev, frame, uf, stream->tt_usecs))
			return 0;
#else
		/* tt must be idle for start(s), any gap, and csplit.
		 * assume scheduling slop leaves 10+% for control/bulk.
		 */
		if (!tt_no_collision (ehci, period_uframes << 3,
				stream->udev, frame, mask))
			return 0;
#endif

		/* check starts (OUT uses more than one) */
		max_used = 100 - stream->usecs;
		for (tmp = stream->raw_mask & 0xff; tmp; tmp >>= 1, uf++) {
			if (periodic_usecs (ehci, frame, uf) > max_used)
				return 0;
		}

		/* for IN, check CSPLIT */
		if (stream->c_usecs) {
			uf = uframe & 7;
			max_used = 100 - stream->c_usecs;
			do {
				tmp = 1 << uf;
				tmp <<= 8;
				if ((stream->raw_mask & tmp) == 0)
					continue;
				if (periodic_usecs (ehci, frame, uf)
						> max_used)
					return 0;
			} while (++uf < 8);
		}

		/* we know urb->interval is 2^N uframes */
		uframe += period_uframes;
	} while (uframe < mod);

	stream->splits = cpu_to_hc32(ehci, stream->raw_mask << (uframe & 7));
	return 1;
}