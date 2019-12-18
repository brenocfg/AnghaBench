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
 int MDIO_DATA_WRITE1 ; 
 int MDIO_SHIFT_CLK ; 
 unsigned int Wn4_PhysicalMgmt ; 
 int /*<<< orphan*/  outw (int,unsigned int) ; 

__attribute__((used)) static void mdio_sync(unsigned int ioaddr, int bits)
{
	unsigned int mdio_addr = ioaddr + Wn4_PhysicalMgmt;

	/* Establish sync by sending at least 32 logic ones. */
	while (-- bits >= 0) {
		outw(MDIO_DATA_WRITE1, mdio_addr);
		outw(MDIO_DATA_WRITE1 | MDIO_SHIFT_CLK, mdio_addr);
	}
}