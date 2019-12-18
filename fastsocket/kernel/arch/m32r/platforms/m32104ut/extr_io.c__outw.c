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
 int /*<<< orphan*/  _ne_outw (unsigned short,int /*<<< orphan*/ ) ; 

void _outw(unsigned short w, unsigned long port)
{
	if (port >= LAN_IOSTART && port < LAN_IOEND)
		_ne_outw(w, PORT2ADDR_NE(port));
	else
		*(volatile unsigned short *)PORT2ADDR(port) = w;
}