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
 unsigned int AUTOINCflag ; 
 int /*<<< orphan*/  _ADDR_HI ; 
 int /*<<< orphan*/  _ADDR_LO ; 
 int /*<<< orphan*/  _MEMDATA ; 
 int /*<<< orphan*/  get_buffer_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_whole_buffer(struct net_device *dev, unsigned offset, unsigned length, char *dest)
{
	int ioaddr = dev->base_addr;

	outb((offset >> 8) | AUTOINCflag, _ADDR_HI);
	outb(offset & 0xff, _ADDR_LO);

	while (length--)
#ifdef ONE_AT_A_TIME_RX
		*(dest++) = get_buffer_byte(dev, offset++);
#else
		*(dest++) = inb(_MEMDATA);
#endif
}