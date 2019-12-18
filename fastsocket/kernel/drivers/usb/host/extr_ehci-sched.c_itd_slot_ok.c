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
typedef  int u8 ;
typedef  int u32 ;
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 int periodic_usecs (struct ehci_hcd*,int,int) ; 

__attribute__((used)) static inline int
itd_slot_ok (
	struct ehci_hcd		*ehci,
	u32			mod,
	u32			uframe,
	u8			usecs,
	u32			period
)
{
	uframe %= period;
	do {
		/* can't commit more than 80% periodic == 100 usec */
		if (periodic_usecs (ehci, uframe >> 3, uframe & 0x7)
				> (100 - usecs))
			return 0;

		/* we know urb->interval is 2^N uframes */
		uframe += period;
	} while (uframe < mod);
	return 1;
}