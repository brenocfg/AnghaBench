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
struct udc_ep {int naking; int /*<<< orphan*/  dev; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int AMD_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  UDC_EPCTL_NAK ; 
 int cnak_pending ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void UDC_QUEUE_CNAK(struct udc_ep *ep, unsigned num)
{
	if (readl(&ep->regs->ctl) & AMD_BIT(UDC_EPCTL_NAK)) {
		DBG(ep->dev, "NAK could not be cleared for ep%d\n", num);
		cnak_pending |= 1 << (num);
		ep->naking = 1;
	} else
		cnak_pending = cnak_pending & (~(1 << (num)));
}