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
struct ehci_sitd {unsigned int index; void** hw_buf_hi; void** hw_buf; void* hw_backpointer; int /*<<< orphan*/  hw_results; int /*<<< orphan*/  hw_uframe; int /*<<< orphan*/  hw_fullspeed_ep; void* hw_next; } ;
struct ehci_iso_stream {int /*<<< orphan*/  splits; int /*<<< orphan*/  address; } ;
struct ehci_iso_sched {struct ehci_iso_packet* packet; } ;
struct ehci_iso_packet {int bufp; int buf1; scalar_t__ cross; int /*<<< orphan*/  transaction; } ;
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 void* EHCI_LIST_END (struct ehci_hcd*) ; 
 void* cpu_to_hc32 (struct ehci_hcd*,int) ; 

__attribute__((used)) static inline void
sitd_patch(
	struct ehci_hcd		*ehci,
	struct ehci_iso_stream	*stream,
	struct ehci_sitd	*sitd,
	struct ehci_iso_sched	*iso_sched,
	unsigned		index
)
{
	struct ehci_iso_packet	*uf = &iso_sched->packet [index];
	u64			bufp = uf->bufp;

	sitd->hw_next = EHCI_LIST_END(ehci);
	sitd->hw_fullspeed_ep = stream->address;
	sitd->hw_uframe = stream->splits;
	sitd->hw_results = uf->transaction;
	sitd->hw_backpointer = EHCI_LIST_END(ehci);

	bufp = uf->bufp;
	sitd->hw_buf[0] = cpu_to_hc32(ehci, bufp);
	sitd->hw_buf_hi[0] = cpu_to_hc32(ehci, bufp >> 32);

	sitd->hw_buf[1] = cpu_to_hc32(ehci, uf->buf1);
	if (uf->cross)
		bufp += 4096;
	sitd->hw_buf_hi[1] = cpu_to_hc32(ehci, bufp >> 32);
	sitd->index = index;
}