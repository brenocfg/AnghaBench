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
struct usb_hcd {int dummy; } ;
struct TYPE_6__ {struct ehci_qh* qh; } ;
struct ehci_qh {struct ehci_qh* reclaim; TYPE_3__ qh_next; } ;
struct ehci_hcd {int /*<<< orphan*/  lock; struct ehci_qh* reclaim; TYPE_2__* async; } ;
struct debug_buffer {char* output_buf; unsigned int alloc_size; int /*<<< orphan*/  bus; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {struct ehci_qh* qh; } ;
struct TYPE_5__ {TYPE_1__ qh_next; } ;

/* Variables and functions */
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 struct ehci_hcd* hcd_to_ehci (struct usb_hcd*) ; 
 int /*<<< orphan*/  qh_lines (struct ehci_hcd*,struct ehci_qh*,char**,unsigned int*) ; 
 unsigned int scnprintf (char*,unsigned int,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t fill_async_buffer(struct debug_buffer *buf)
{
	struct usb_hcd		*hcd;
	struct ehci_hcd		*ehci;
	unsigned long		flags;
	unsigned		temp, size;
	char			*next;
	struct ehci_qh		*qh;

	hcd = bus_to_hcd(buf->bus);
	ehci = hcd_to_ehci (hcd);
	next = buf->output_buf;
	size = buf->alloc_size;

	*next = 0;

	/* dumps a snapshot of the async schedule.
	 * usually empty except for long-term bulk reads, or head.
	 * one QH per line, and TDs we know about
	 */
	spin_lock_irqsave (&ehci->lock, flags);
	for (qh = ehci->async->qh_next.qh; size > 0 && qh; qh = qh->qh_next.qh)
		qh_lines (ehci, qh, &next, &size);
	if (ehci->reclaim && size > 0) {
		temp = scnprintf (next, size, "\nreclaim =\n");
		size -= temp;
		next += temp;

		for (qh = ehci->reclaim; size > 0 && qh; qh = qh->reclaim)
			qh_lines (ehci, qh, &next, &size);
	}
	spin_unlock_irqrestore (&ehci->lock, flags);

	return strlen(buf->output_buf);
}