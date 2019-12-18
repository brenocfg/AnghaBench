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
 scalar_t__ ETHER_IOMAP (unsigned long) ; 
 scalar_t__ PXSEG (unsigned long) ; 
 int* port2adr (unsigned long) ; 

unsigned char sh7751systemh_inb(unsigned long port)
{
	if (PXSEG(port))
		return *(volatile unsigned char *)port;
	else if (port <= 0x3F1)
		return *(volatile unsigned char *)ETHER_IOMAP(port);
	else
		return (*port2adr(port))&0xff;
}