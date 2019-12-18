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
struct ehci_itd {int* index; int /*<<< orphan*/ * hw_bufp; int /*<<< orphan*/  hw_next; } ;
struct ehci_iso_stream {int /*<<< orphan*/  buf2; int /*<<< orphan*/  buf1; int /*<<< orphan*/  buf0; } ;
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCI_LIST_END (struct ehci_hcd*) ; 

__attribute__((used)) static inline void
itd_init(struct ehci_hcd *ehci, struct ehci_iso_stream *stream,
		struct ehci_itd *itd)
{
	int i;

	/* it's been recently zeroed */
	itd->hw_next = EHCI_LIST_END(ehci);
	itd->hw_bufp [0] = stream->buf0;
	itd->hw_bufp [1] = stream->buf1;
	itd->hw_bufp [2] = stream->buf2;

	for (i = 0; i < 8; i++)
		itd->index[i] = -1;

	/* All other fields are filled when scheduling */
}