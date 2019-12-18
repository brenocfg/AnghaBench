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
struct ohci_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  ed_bulktail; int /*<<< orphan*/  ed_controltail; } ;
struct debug_buffer {scalar_t__ count; scalar_t__ page; struct ohci_hcd* ohci; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t show_list (struct ohci_hcd*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static ssize_t fill_async_buffer(struct debug_buffer *buf)
{
	struct ohci_hcd		*ohci;
	size_t			temp;
	unsigned long		flags;

	ohci = buf->ohci;

	/* display control and bulk lists together, for simplicity */
	spin_lock_irqsave (&ohci->lock, flags);
	temp = show_list(ohci, buf->page, buf->count, ohci->ed_controltail);
	temp += show_list(ohci, buf->page + temp, buf->count - temp,
			  ohci->ed_bulktail);
	spin_unlock_irqrestore (&ohci->lock, flags);

	return temp;
}