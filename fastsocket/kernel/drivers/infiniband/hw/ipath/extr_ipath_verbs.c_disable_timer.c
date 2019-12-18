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
typedef  int /*<<< orphan*/  u64 ;
struct ipath_devdata {int ipath_flags; int /*<<< orphan*/  verbs_timer; int /*<<< orphan*/  ipath_gpio_mask; TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  kr_gpio_mask; } ;

/* Variables and functions */
 int IPATH_GPIO_INTR ; 
 int IPATH_GPIO_PORT0_BIT ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int disable_timer(struct ipath_devdata *dd)
{
	/* Disable GPIO bit 2 interrupt */
	if (dd->ipath_flags & IPATH_GPIO_INTR) {
                /* Disable GPIO bit 2 interrupt */
		dd->ipath_gpio_mask &= ~((u64) (1 << IPATH_GPIO_PORT0_BIT));
		ipath_write_kreg(dd, dd->ipath_kregs->kr_gpio_mask,
				 dd->ipath_gpio_mask);
		/*
		 * We might want to undo changes to debugportselect,
		 * but how?
		 */
	}

	del_timer_sync(&dd->verbs_timer);

	return 0;
}