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
union ehci_shadow {TYPE_4__* sitd; TYPE_3__* itd; TYPE_2__* fstn; TYPE_1__* qh; } ;
struct ehci_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  __hc32 ;
struct TYPE_8__ {union ehci_shadow sitd_next; } ;
struct TYPE_7__ {union ehci_shadow itd_next; } ;
struct TYPE_6__ {union ehci_shadow fstn_next; } ;
struct TYPE_5__ {union ehci_shadow qh_next; } ;

/* Variables and functions */
#define  Q_TYPE_FSTN 130 
#define  Q_TYPE_ITD 129 
#define  Q_TYPE_QH 128 
 int hc32_to_cpu (struct ehci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static union ehci_shadow *
periodic_next_shadow(struct ehci_hcd *ehci, union ehci_shadow *periodic,
		__hc32 tag)
{
	switch (hc32_to_cpu(ehci, tag)) {
	case Q_TYPE_QH:
		return &periodic->qh->qh_next;
	case Q_TYPE_FSTN:
		return &periodic->fstn->fstn_next;
	case Q_TYPE_ITD:
		return &periodic->itd->itd_next;
	// case Q_TYPE_SITD:
	default:
		return &periodic->sitd->sitd_next;
	}
}