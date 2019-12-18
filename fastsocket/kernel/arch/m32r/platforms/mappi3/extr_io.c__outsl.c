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
 unsigned char* PORT2ADDR (unsigned int) ; 

void _outsl(unsigned int port, const void * addr, unsigned long count)
{
	const unsigned long *buf = addr;
	unsigned char *portp;

	portp = PORT2ADDR(port);
	while (count--)
		*(volatile unsigned long *)portp = *buf++;
}