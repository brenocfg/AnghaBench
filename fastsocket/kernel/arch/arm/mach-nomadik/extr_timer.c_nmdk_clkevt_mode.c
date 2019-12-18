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
struct clock_event_device {int dummy; } ;
typedef  enum clock_event_mode { ____Placeholder_clock_event_mode } clock_event_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  CLOCK_EVT_MODE_ONESHOT 132 
#define  CLOCK_EVT_MODE_PERIODIC 131 
#define  CLOCK_EVT_MODE_RESUME 130 
#define  CLOCK_EVT_MODE_SHUTDOWN 129 
#define  CLOCK_EVT_MODE_UNUSED 128 
 scalar_t__ MTU_IMSC ; 
 scalar_t__ mtu_base ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void nmdk_clkevt_mode(enum clock_event_mode mode,
			     struct clock_event_device *dev)
{
	unsigned long flags;

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		/* enable interrupts -- and count current value? */
		raw_local_irq_save(flags);
		writel(readl(mtu_base + MTU_IMSC) | 1, mtu_base + MTU_IMSC);
		raw_local_irq_restore(flags);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		BUG(); /* Not supported, yet */
		/* FALLTHROUGH */
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_UNUSED:
		/* disable irq */
		raw_local_irq_save(flags);
		writel(readl(mtu_base + MTU_IMSC) & ~1, mtu_base + MTU_IMSC);
		raw_local_irq_restore(flags);
		break;
	case CLOCK_EVT_MODE_RESUME:
		break;
	}
}