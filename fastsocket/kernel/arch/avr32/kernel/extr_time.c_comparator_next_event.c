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

/* Variables and functions */
 int /*<<< orphan*/  COMPARE ; 
 int /*<<< orphan*/  COUNT ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 scalar_t__ sysreg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int comparator_next_event(unsigned long delta,
		struct clock_event_device *evdev)
{
	unsigned long	flags;

	raw_local_irq_save(flags);

	/* The time to read COUNT then update COMPARE must be less
	 * than the min_delta_ns value for this clockevent source.
	 */
	sysreg_write(COMPARE, (sysreg_read(COUNT) + delta) ? : 1);

	raw_local_irq_restore(flags);

	return 0;
}