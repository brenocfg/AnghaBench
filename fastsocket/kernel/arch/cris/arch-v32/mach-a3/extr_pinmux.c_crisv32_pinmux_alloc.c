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
typedef  enum pin_mode { ____Placeholder_pin_mode } pin_mode ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int PORTS ; 
 int PORT_PINS ; 
 int /*<<< orphan*/  crisv32_pinmux_init () ; 
 int /*<<< orphan*/  crisv32_pinmux_set (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ pinmux_gpio ; 
 int /*<<< orphan*/  pinmux_lock ; 
 scalar_t__ pinmux_none ; 
 scalar_t__* pins ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
crisv32_pinmux_alloc(int port, int first_pin, int last_pin, enum pin_mode mode)
{
	int i;
	unsigned long flags;

	crisv32_pinmux_init();

	if (port >= PORTS)
		return -EINVAL;

	spin_lock_irqsave(&pinmux_lock, flags);

	for (i = first_pin; i <= last_pin; i++) {
		if ((pins[port * PORT_PINS + i] != pinmux_none) &&
		    (pins[port * PORT_PINS + i] != pinmux_gpio) &&
		    (pins[port * PORT_PINS + i] != mode)) {
			spin_unlock_irqrestore(&pinmux_lock, flags);
#ifdef DEBUG
			panic("Pinmux alloc failed!\n");
#endif
			return -EPERM;
		}
	}

	for (i = first_pin; i <= last_pin; i++)
		pins[port * PORT_PINS + i] = mode;

	crisv32_pinmux_set(port);

	spin_unlock_irqrestore(&pinmux_lock, flags);

	return 0;
}