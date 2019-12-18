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
 int /*<<< orphan*/  PORT2ADDR_NE (unsigned int) ; 
 int /*<<< orphan*/  _ne_insb (int /*<<< orphan*/ ,void*,unsigned long) ; 

void _insb(unsigned int port, void *addr, unsigned long count)
{
	if (port >= LAN_IOSTART && port < LAN_IOEND)
		_ne_insb(PORT2ADDR_NE(port), addr, count);
	else {
		unsigned char *buf = addr;
		unsigned char *portp = PORT2ADDR(port);
		while (count--)
			*buf++ = *(volatile unsigned char *)portp;
	}
}