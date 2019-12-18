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
typedef  int u16 ;

/* Variables and functions */
 int inl (unsigned long) ; 
 int /*<<< orphan*/  outl (int,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static u16 phy_read_1bit(unsigned long ioaddr)
{
	u16 phy_data;

	outl(0x50000, ioaddr);
	udelay(1);
	phy_data = ( inl(ioaddr) >> 19 ) & 0x1;
	outl(0x40000, ioaddr);
	udelay(1);

	return phy_data;
}