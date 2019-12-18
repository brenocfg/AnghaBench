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

void microdev_outsw(unsigned long port, const void *buffer, unsigned long count)
{
	volatile unsigned short *port_addr;
	const unsigned short *buf = buffer;

	port_addr = (volatile unsigned short *)PORT2ADDR(port);

	while (count--)
		*port_addr = *buf++;
}