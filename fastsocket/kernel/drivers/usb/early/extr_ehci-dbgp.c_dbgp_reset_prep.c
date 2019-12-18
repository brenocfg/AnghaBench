#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int index; int flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int CON_BOOT ; 
 int DBGP_CLAIM ; 
 int DBGP_ENABLED ; 
 int dbgp_not_safe ; 
 TYPE_2__ early_dbgp_console ; 
 TYPE_1__* ehci_debug ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

int dbgp_reset_prep(void)
{
	u32 ctrl;

	dbgp_not_safe = 1;
	if (!ehci_debug)
		return 0;

	if (early_dbgp_console.index != -1 &&
		!(early_dbgp_console.flags & CON_BOOT))
		return 1;
	/* This means the console is not initialized, or should get
	 * shutdown so as to allow for reuse of the usb device, which
	 * means it is time to shutdown the usb debug port. */
	ctrl = readl(&ehci_debug->control);
	if (ctrl & DBGP_ENABLED) {
		ctrl &= ~(DBGP_CLAIM);
		writel(ctrl, &ehci_debug->control);
	}
	return 0;
}