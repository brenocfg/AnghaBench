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
 unsigned long SMC_IOADDR ; 
 int /*<<< orphan*/  maybebadio (unsigned long) ; 

__attribute__((used)) static unsigned long sh_edosk7705_isa_port2addr(unsigned long port)
{
	/*
	 * SMC91C96 registers are 4 byte aligned rather than the
	 * usual 2 byte!
	 */
	if (port >= 0x300 && port < 0x320)
		return SMC_IOADDR + ((port - 0x300) * 2);

	maybebadio(port);
	return port;
}