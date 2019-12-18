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
 unsigned long LAN_IOEND ; 
 unsigned long LAN_IOSTART ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 int /*<<< orphan*/  PORT2ADDR_NE (unsigned long) ; 
 unsigned char _ne_inb (int /*<<< orphan*/ ) ; 

unsigned char _inb(unsigned long port)
{
	if (port >= LAN_IOSTART && port < LAN_IOEND)
		return _ne_inb(PORT2ADDR_NE(port));

	return *(volatile unsigned char *)PORT2ADDR(port);
}