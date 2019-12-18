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
 scalar_t__ PORT2ADDR (unsigned long) ; 

void microdev_insb(unsigned long port, void *buffer, unsigned long count)
{
	volatile unsigned char *port_addr;
	unsigned char *buf = buffer;

	port_addr = (volatile unsigned char *)PORT2ADDR(port);

	while (count--)
		*buf++ = *port_addr;
}