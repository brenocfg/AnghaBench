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
 int RDDATAflag ; 
 int /*<<< orphan*/  TIME (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ADDR_HI ; 
 int /*<<< orphan*/  _ADDR_LO ; 
 int /*<<< orphan*/  _MEMDATA ; 
 int /*<<< orphan*/  insb (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void com20020_copy_from_card(struct net_device *dev, int bufnum,
				    int offset, void *buf, int count)
{
	int ioaddr = dev->base_addr, ofs = 512 * bufnum + offset;

	/* set up the address register */
	outb((ofs >> 8) | RDDATAflag | AUTOINCflag, _ADDR_HI);
	outb(ofs & 0xff, _ADDR_LO);

	/* copy the data */
	TIME("insb", count, insb(_MEMDATA, buf, count));
}