#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_5__ {unsigned long data; scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct ipath_devdata {int ipath_flags; int ipath_gpio_mask; TYPE_2__ verbs_timer; TYPE_1__* ipath_kregs; } ;
struct TYPE_4__ {int /*<<< orphan*/  kr_gpio_mask; int /*<<< orphan*/  kr_debugportselect; } ;

/* Variables and functions */
 int IPATH_GPIO_INTR ; 
 int IPATH_GPIO_PORT0_BIT ; 
 int /*<<< orphan*/  __verbs_timer ; 
 int /*<<< orphan*/  add_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static int enable_timer(struct ipath_devdata *dd)
{
	/*
	 * Early chips had a design flaw where the chip and kernel idea
	 * of the tail register don't always agree, and therefore we won't
	 * get an interrupt on the next packet received.
	 * If the board supports per packet receive interrupts, use it.
	 * Otherwise, the timer function periodically checks for packets
	 * to cover this case.
	 * Either way, the timer is needed for verbs layer related
	 * processing.
	 */
	if (dd->ipath_flags & IPATH_GPIO_INTR) {
		ipath_write_kreg(dd, dd->ipath_kregs->kr_debugportselect,
				 0x2074076542310ULL);
		/* Enable GPIO bit 2 interrupt */
		dd->ipath_gpio_mask |= (u64) (1 << IPATH_GPIO_PORT0_BIT);
		ipath_write_kreg(dd, dd->ipath_kregs->kr_gpio_mask,
				 dd->ipath_gpio_mask);
	}

	init_timer(&dd->verbs_timer);
	dd->verbs_timer.function = __verbs_timer;
	dd->verbs_timer.data = (unsigned long)dd;
	dd->verbs_timer.expires = jiffies + 1;
	add_timer(&dd->verbs_timer);

	return 0;
}