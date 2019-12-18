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
 unsigned short* PORT2ADDR (unsigned int) ; 
 unsigned short* PORT2ADDR_NE (unsigned int) ; 
 int /*<<< orphan*/  _ne_outw (int /*<<< orphan*/ ,unsigned short*) ; 

void _outsw(unsigned int port, const void *addr, unsigned long count)
{
	const unsigned short *buf = addr;
	unsigned short *portp;

	if (port >= 0x300 && port < 0x320) {
		portp = PORT2ADDR_NE(port);
		while (count--)
			_ne_outw(*buf++, portp);
	} else {
		portp = PORT2ADDR(port);
		while (count--)
			*(volatile unsigned short *)portp = *buf++;
	}
}