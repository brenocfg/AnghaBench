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
struct crisv32_iopin {int bit; TYPE_1__* port; } ;
struct TYPE_2__ {int pin_count; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 TYPE_1__* crisv32_ioports ; 
 scalar_t__ crisv32_pinmux_alloc (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pinmux_gpio ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 char toupper (char const) ; 

int crisv32_io_get_name(struct crisv32_iopin *iopin, const char *name)
{
	int port;
	int pin;

	if (toupper(*name) == 'P')
		name++;

	if (toupper(*name) < 'A' || toupper(*name) > 'E')
		return -EINVAL;

	port = toupper(*name) - 'A';
	name++;
	pin = simple_strtoul(name, NULL, 10);

	if (pin < 0 || pin > crisv32_ioports[port].pin_count)
		return -EINVAL;

	iopin->bit = 1 << pin;
	iopin->port = &crisv32_ioports[port];

	if (crisv32_pinmux_alloc(port, pin, pin, pinmux_gpio))
		return -EIO;

	return 0;
}