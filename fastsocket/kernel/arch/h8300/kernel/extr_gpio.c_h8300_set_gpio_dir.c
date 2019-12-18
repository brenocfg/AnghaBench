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
struct TYPE_2__ {int used; int ddr; } ;

/* Variables and functions */
 int** ddrs ; 
 TYPE_1__* gpio_regs ; 

int h8300_set_gpio_dir(int port_bit,int dir)
{
	int port = (port_bit >> 8) & 0xff;
	int bit  = port_bit & 0xff;

	if (ddrs[port] == NULL)
		return 0;
	if (gpio_regs[port].used & bit) {
		if (dir)
			gpio_regs[port].ddr |= bit;
		else
			gpio_regs[port].ddr &= ~bit;
		*ddrs[port] = gpio_regs[port].ddr;
		return 1;
	} else
		return 0;
}