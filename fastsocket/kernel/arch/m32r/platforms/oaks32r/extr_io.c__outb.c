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
 int /*<<< orphan*/  PORT2ADDR_NE (unsigned long) ; 
 int /*<<< orphan*/  _ne_outb (unsigned char,int /*<<< orphan*/ ) ; 

void _outb(unsigned char b, unsigned long port)
{
	if (port >= 0x300 && port < 0x320)
		_ne_outb(b, PORT2ADDR_NE(port));
	else
		*(volatile unsigned char *)PORT2ADDR(port) = b;
}