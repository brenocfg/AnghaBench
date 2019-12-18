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
union ehci_shadow {struct ehci_itd* itd; scalar_t__ ptr; } ;
struct ehci_itd {unsigned int frame; int itd_dma; scalar_t__ hw_next; union ehci_shadow itd_next; } ;
struct ehci_hcd {scalar_t__* periodic; union ehci_shadow* pshadow; } ;
typedef  scalar_t__ __hc32 ;

/* Variables and functions */
 scalar_t__ Q_NEXT_TYPE (struct ehci_hcd*,scalar_t__) ; 
 int Q_TYPE_ITD ; 
 int Q_TYPE_QH ; 
 scalar_t__ cpu_to_hc32 (struct ehci_hcd*,int) ; 
 union ehci_shadow* periodic_next_shadow (struct ehci_hcd*,union ehci_shadow*,scalar_t__) ; 
 scalar_t__* shadow_next_periodic (struct ehci_hcd*,union ehci_shadow*,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
itd_link (struct ehci_hcd *ehci, unsigned frame, struct ehci_itd *itd)
{
	union ehci_shadow	*prev = &ehci->pshadow[frame];
	__hc32			*hw_p = &ehci->periodic[frame];
	union ehci_shadow	here = *prev;
	__hc32			type = 0;

	/* skip any iso nodes which might belong to previous microframes */
	while (here.ptr) {
		type = Q_NEXT_TYPE(ehci, *hw_p);
		if (type == cpu_to_hc32(ehci, Q_TYPE_QH))
			break;
		prev = periodic_next_shadow(ehci, prev, type);
		hw_p = shadow_next_periodic(ehci, &here, type);
		here = *prev;
	}

	itd->itd_next = here;
	itd->hw_next = *hw_p;
	prev->itd = itd;
	itd->frame = frame;
	wmb ();
	*hw_p = cpu_to_hc32(ehci, itd->itd_dma | Q_TYPE_ITD);
}