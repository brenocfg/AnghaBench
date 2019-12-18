#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct ehci_sitd* sitd; } ;
struct ehci_sitd {unsigned int frame; int sitd_dma; int /*<<< orphan*/  hw_next; TYPE_1__ sitd_next; } ;
struct ehci_hcd {int /*<<< orphan*/ * periodic; TYPE_1__* pshadow; } ;

/* Variables and functions */
 int Q_TYPE_SITD ; 
 int /*<<< orphan*/  cpu_to_hc32 (struct ehci_hcd*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
sitd_link (struct ehci_hcd *ehci, unsigned frame, struct ehci_sitd *sitd)
{
	/* note: sitd ordering could matter (CSPLIT then SSPLIT) */
	sitd->sitd_next = ehci->pshadow [frame];
	sitd->hw_next = ehci->periodic [frame];
	ehci->pshadow [frame].sitd = sitd;
	sitd->frame = frame;
	wmb ();
	ehci->periodic[frame] = cpu_to_hc32(ehci, sitd->sitd_dma | Q_TYPE_SITD);
}