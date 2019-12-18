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
 int PORTS ; 
 int PORT_PINS ; 
 int /*<<< orphan*/  crisv32_pinmux_init () ; 
 int /*<<< orphan*/ ** pins ; 
 int /*<<< orphan*/  printk (char*,int,...) ; 

void
crisv32_pinmux_dump(void)
{
	int i, j;

	crisv32_pinmux_init();

	for (i = 0; i < PORTS; i++)
	{
		printk("Port %c\n", 'B'+i);
		for (j = 0; j < PORT_PINS; j++)
			printk("  Pin %d = %d\n", j, pins[i][j]);
	}
}