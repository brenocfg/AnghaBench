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

/* Variables and functions */
 int EINVAL ; 
 int PORTS ; 
 int /*<<< orphan*/  crisv32_pinmux_init () ; 
 int /*<<< orphan*/  crisv32_pinmux_set (int) ; 
 int /*<<< orphan*/  pinmux_lock ; 
 int /*<<< orphan*/  pinmux_none ; 
 int /*<<< orphan*/ ** pins ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
crisv32_pinmux_dealloc(int port, int first_pin, int last_pin)
{
	int i;
	unsigned long flags;

	crisv32_pinmux_init();

	if (port > PORTS)
		return -EINVAL;

	spin_lock_irqsave(&pinmux_lock, flags);

	for (i = first_pin; i <= last_pin; i++)
		pins[port][i] = pinmux_none;

	crisv32_pinmux_set(port);
	spin_unlock_irqrestore(&pinmux_lock, flags);

	return 0;
}