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
 unsigned char __raw_readb (int /*<<< orphan*/ ) ; 
 int __raw_readw (unsigned long) ; 
 int /*<<< orphan*/  sh_edosk7705_isa_port2addr (unsigned long) ; 

unsigned char sh_edosk7705_inb(unsigned long port)
{
	if (port >= 0x300 && port < 0x320 && port & 0x01)
		return __raw_readw(port - 1) >> 8;

	return __raw_readb(sh_edosk7705_isa_port2addr(port));
}