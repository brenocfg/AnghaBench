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
 unsigned int LAN_IOEND ; 
 unsigned int LAN_IOSTART ; 
 unsigned char* PORT2ADDR (unsigned int) ; 
 unsigned char* PORT2ADDR_NE (unsigned int) ; 
 int /*<<< orphan*/  _ne_outb (int /*<<< orphan*/ ,unsigned char*) ; 

void _outsb(unsigned int port, const void *addr, unsigned long count)
{
	const unsigned char *buf = addr;
	unsigned char *portp;

	if (port >= LAN_IOSTART && port < LAN_IOEND) {
		portp = PORT2ADDR_NE(port);
		while (count--)
			_ne_outb(*buf++, portp);
	} else {
		portp = PORT2ADDR(port);
		while (count--)
			*(volatile unsigned char *)portp = *buf++;
	}
}