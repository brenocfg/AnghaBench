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
 int current_gpio_io ; 
 int /*<<< orphan*/  wb977_device_select (int) ; 
 int /*<<< orphan*/  wb977_wb (int,unsigned int) ; 

__attribute__((used)) static inline void __gpio_modify_io(int mask, int in)
{
	unsigned int new_gpio, changed;
	int port;

	new_gpio = (current_gpio_io & ~mask) | in;
	changed = new_gpio ^ current_gpio_io;
	current_gpio_io = new_gpio;

	changed >>= 1;
	new_gpio >>= 1;

	wb977_device_select(7);

	for (port = 0xe1; changed && port < 0xe8; changed >>= 1) {
		wb977_wb(port, new_gpio & 1);

		port += 1;
		new_gpio >>= 1;
	}

	wb977_device_select(8);

	for (port = 0xe8; changed && port < 0xec; changed >>= 1) {
		wb977_wb(port, new_gpio & 1);

		port += 1;
		new_gpio >>= 1;
	}
}