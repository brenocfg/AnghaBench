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
 int /*<<< orphan*/  BUS2QUAD (unsigned int) ; 
 unsigned int PCI_CONF1_MQ_ADDRESS (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  XQUAD_PORT_ADDR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (unsigned int,int) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ xquad_portio ; 

__attribute__((used)) static void write_cf8(unsigned bus, unsigned devfn, unsigned reg)
{
	unsigned val = PCI_CONF1_MQ_ADDRESS(bus, devfn, reg);
	if (xquad_portio)
		writel(val, XQUAD_PORT_ADDR(0xcf8, BUS2QUAD(bus)));
	else
		outl(val, 0xCF8);
}