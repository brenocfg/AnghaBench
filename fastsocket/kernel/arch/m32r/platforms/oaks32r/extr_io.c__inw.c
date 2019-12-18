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
 unsigned short _ne_inw (int /*<<< orphan*/ ) ; 

unsigned short _inw(unsigned long port)
{
	if (port >= 0x300 && port < 0x320)
		return _ne_inw(PORT2ADDR_NE(port));

	return *(volatile unsigned short *)PORT2ADDR(port);
}