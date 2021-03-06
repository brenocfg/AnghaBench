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
struct net_device {int base_addr; } ;

/* Variables and functions */
 int AUTOINCflag ; 
 int /*<<< orphan*/  TIME (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ADDR_HI ; 
 int /*<<< orphan*/  _ADDR_LO ; 
 int /*<<< orphan*/  _MEMDATA ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outsb (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void com20020_copy_to_card(struct net_device *dev, int bufnum,
				  int offset, void *buf, int count)
{
	int ioaddr = dev->base_addr, ofs = 512 * bufnum + offset;

	/* set up the address register */
	outb((ofs >> 8) | AUTOINCflag, _ADDR_HI);
	outb(ofs & 0xff, _ADDR_LO);

	/* copy the data */
	TIME("outsb", count, outsb(_MEMDATA, buf, count));
}