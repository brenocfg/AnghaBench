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
union ehci_shadow {struct ehci_qh* qh; scalar_t__ ptr; } ;
struct ehci_qh {unsigned int period; unsigned int start; int usecs; int c_usecs; scalar_t__ xacterrs; int /*<<< orphan*/  qh_state; int /*<<< orphan*/  qh_dma; TYPE_2__* hw; union ehci_shadow qh_next; TYPE_1__* dev; } ;
struct ehci_hcd {unsigned int periodic_size; scalar_t__* periodic; union ehci_shadow* pshadow; } ;
typedef  scalar_t__ __hc32 ;
struct TYPE_7__ {int bandwidth_allocated; } ;
struct TYPE_8__ {TYPE_3__ self; } ;
struct TYPE_6__ {scalar_t__ hw_next; int /*<<< orphan*/  hw_info2; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int QH_CMASK ; 
 scalar_t__ QH_NEXT (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int QH_SMASK ; 
 int /*<<< orphan*/  QH_STATE_LINKED ; 
 scalar_t__ Q_NEXT_TYPE (struct ehci_hcd*,scalar_t__) ; 
 int /*<<< orphan*/  Q_TYPE_QH ; 
 scalar_t__ cpu_to_hc32 (struct ehci_hcd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int,struct ehci_qh*,unsigned int,int,int) ; 
 TYPE_4__* ehci_to_hcd (struct ehci_hcd*) ; 
 int enable_periodic (struct ehci_hcd*) ; 
 int hc32_to_cpup (struct ehci_hcd*,int /*<<< orphan*/ *) ; 
 union ehci_shadow* periodic_next_shadow (struct ehci_hcd*,union ehci_shadow*,scalar_t__) ; 
 int /*<<< orphan*/  qh_get (struct ehci_qh*) ; 
 scalar_t__* shadow_next_periodic (struct ehci_hcd*,union ehci_shadow*,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int qh_link_periodic (struct ehci_hcd *ehci, struct ehci_qh *qh)
{
	unsigned	i;
	unsigned	period = qh->period;

	dev_dbg (&qh->dev->dev,
		"link qh%d-%04x/%p start %d [%d/%d us]\n",
		period, hc32_to_cpup(ehci, &qh->hw->hw_info2)
			& (QH_CMASK | QH_SMASK),
		qh, qh->start, qh->usecs, qh->c_usecs);

	/* high bandwidth, or otherwise every microframe */
	if (period == 0)
		period = 1;

	for (i = qh->start; i < ehci->periodic_size; i += period) {
		union ehci_shadow	*prev = &ehci->pshadow[i];
		__hc32			*hw_p = &ehci->periodic[i];
		union ehci_shadow	here = *prev;
		__hc32			type = 0;

		/* skip the iso nodes at list head */
		while (here.ptr) {
			type = Q_NEXT_TYPE(ehci, *hw_p);
			if (type == cpu_to_hc32(ehci, Q_TYPE_QH))
				break;
			prev = periodic_next_shadow(ehci, prev, type);
			hw_p = shadow_next_periodic(ehci, &here, type);
			here = *prev;
		}

		/* sorting each branch by period (slow-->fast)
		 * enables sharing interior tree nodes
		 */
		while (here.ptr && qh != here.qh) {
			if (qh->period > here.qh->period)
				break;
			prev = &here.qh->qh_next;
			hw_p = &here.qh->hw->hw_next;
			here = *prev;
		}
		/* link in this qh, unless some earlier pass did that */
		if (qh != here.qh) {
			qh->qh_next = here;
			if (here.qh)
				qh->hw->hw_next = *hw_p;
			wmb ();
			prev->qh = qh;
			*hw_p = QH_NEXT (ehci, qh->qh_dma);
		}
	}
	qh->qh_state = QH_STATE_LINKED;
	qh->xacterrs = 0;
	qh_get (qh);

	/* update per-qh bandwidth for usbfs */
	ehci_to_hcd(ehci)->self.bandwidth_allocated += qh->period
		? ((qh->usecs + qh->c_usecs) / qh->period)
		: (qh->usecs * 8);

	/* maybe enable periodic schedule processing */
	return enable_periodic(ehci);
}