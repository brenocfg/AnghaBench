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
struct TYPE_2__ {int /*<<< orphan*/ * field; } ;
union xhci_trb {TYPE_1__ generic; } ;
struct xhci_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*,int,int /*<<< orphan*/ ) ; 

void xhci_print_trb_offsets(struct xhci_hcd *xhci, union xhci_trb *trb)
{
	int i;
	for (i = 0; i < 4; ++i)
		xhci_dbg(xhci, "Offset 0x%x = 0x%x\n",
				i*4, trb->generic.field[i]);
}