#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union ehci_shadow {TYPE_4__* sitd; TYPE_2__* qh; TYPE_1__* itd; scalar_t__ ptr; } ;
typedef  int u32 ;
typedef  int u16 ;
struct usb_device {int dummy; } ;
struct ehci_qh_hw {int /*<<< orphan*/  hw_next; int /*<<< orphan*/  hw_info2; } ;
struct ehci_hcd {unsigned int periodic_size; int /*<<< orphan*/ * periodic; union ehci_shadow* pshadow; } ;
typedef  int /*<<< orphan*/  __hc32 ;
struct TYPE_8__ {union ehci_shadow sitd_next; int /*<<< orphan*/  hw_next; int /*<<< orphan*/  hw_uframe; TYPE_3__* urb; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {union ehci_shadow qh_next; int /*<<< orphan*/  dev; struct ehci_qh_hw* hw; } ;
struct TYPE_5__ {union ehci_shadow itd_next; int /*<<< orphan*/  hw_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_NEXT_TYPE (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
#define  Q_TYPE_ITD 130 
#define  Q_TYPE_QH 129 
#define  Q_TYPE_SITD 128 
 int /*<<< orphan*/  ehci_dbg (struct ehci_hcd*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int hc32_to_cpu (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  same_tt (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tt_no_collision (
	struct ehci_hcd		*ehci,
	unsigned		period,
	struct usb_device	*dev,
	unsigned		frame,
	u32			uf_mask
)
{
	if (period == 0)	/* error */
		return 0;

	/* note bandwidth wastage:  split never follows csplit
	 * (different dev or endpoint) until the next uframe.
	 * calling convention doesn't make that distinction.
	 */
	for (; frame < ehci->periodic_size; frame += period) {
		union ehci_shadow	here;
		__hc32			type;
		struct ehci_qh_hw	*hw;

		here = ehci->pshadow [frame];
		type = Q_NEXT_TYPE(ehci, ehci->periodic [frame]);
		while (here.ptr) {
			switch (hc32_to_cpu(ehci, type)) {
			case Q_TYPE_ITD:
				type = Q_NEXT_TYPE(ehci, here.itd->hw_next);
				here = here.itd->itd_next;
				continue;
			case Q_TYPE_QH:
				hw = here.qh->hw;
				if (same_tt (dev, here.qh->dev)) {
					u32		mask;

					mask = hc32_to_cpu(ehci,
							hw->hw_info2);
					/* "knows" no gap is needed */
					mask |= mask >> 8;
					if (mask & uf_mask)
						break;
				}
				type = Q_NEXT_TYPE(ehci, hw->hw_next);
				here = here.qh->qh_next;
				continue;
			case Q_TYPE_SITD:
				if (same_tt (dev, here.sitd->urb->dev)) {
					u16		mask;

					mask = hc32_to_cpu(ehci, here.sitd
								->hw_uframe);
					/* FIXME assumes no gap for IN! */
					mask |= mask >> 8;
					if (mask & uf_mask)
						break;
				}
				type = Q_NEXT_TYPE(ehci, here.sitd->hw_next);
				here = here.sitd->sitd_next;
				continue;
			// case Q_TYPE_FSTN:
			default:
				ehci_dbg (ehci,
					"periodic frame %d bogus type %d\n",
					frame, type);
			}

			/* collision or error */
			return 0;
		}
	}

	/* no collision */
	return 1;
}