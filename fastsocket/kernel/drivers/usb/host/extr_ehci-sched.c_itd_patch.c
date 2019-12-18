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
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct ehci_itd {unsigned int pg; unsigned int* index; int /*<<< orphan*/ * hw_bufp_hi; int /*<<< orphan*/ * hw_bufp; int /*<<< orphan*/ * hw_transaction; } ;
struct ehci_iso_sched {struct ehci_iso_packet* packet; } ;
struct ehci_iso_packet {int bufp; int /*<<< orphan*/  cross; int /*<<< orphan*/  transaction; } ;
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_hc32 (struct ehci_hcd*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
itd_patch(
	struct ehci_hcd		*ehci,
	struct ehci_itd		*itd,
	struct ehci_iso_sched	*iso_sched,
	unsigned		index,
	u16			uframe
)
{
	struct ehci_iso_packet	*uf = &iso_sched->packet [index];
	unsigned		pg = itd->pg;

	// BUG_ON (pg == 6 && uf->cross);

	uframe &= 0x07;
	itd->index [uframe] = index;

	itd->hw_transaction[uframe] = uf->transaction;
	itd->hw_transaction[uframe] |= cpu_to_hc32(ehci, pg << 12);
	itd->hw_bufp[pg] |= cpu_to_hc32(ehci, uf->bufp & ~(u32)0);
	itd->hw_bufp_hi[pg] |= cpu_to_hc32(ehci, (u32)(uf->bufp >> 32));

	/* iso_frame_desc[].offset must be strictly increasing */
	if (unlikely (uf->cross)) {
		u64	bufp = uf->bufp + 4096;

		itd->pg = ++pg;
		itd->hw_bufp[pg] |= cpu_to_hc32(ehci, bufp & ~(u32)0);
		itd->hw_bufp_hi[pg] |= cpu_to_hc32(ehci, (u32)(bufp >> 32));
	}
}