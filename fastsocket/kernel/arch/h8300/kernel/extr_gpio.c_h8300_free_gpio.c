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
struct TYPE_2__ {unsigned char used; } ;

/* Variables and functions */
 int MAX_PORT ; 
 TYPE_1__* gpio_regs ; 

int h8300_free_gpio(int port, unsigned int bits)
{
	unsigned char *used;

	if (port < 0 || port >= MAX_PORT)
		return -1;
	used = &(gpio_regs[port].used);
	if ((*used & bits) != bits)
		return 0;
	*used &= (~bits);
	return 1;
}