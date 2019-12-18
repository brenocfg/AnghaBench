#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char MCE_bit; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ad1848_info ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_Index_Addr (TYPE_1__*) ; 
 int /*<<< orphan*/  io_Indexed_Data (TYPE_1__*) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_write(ad1848_info * devc, int reg, int data)
{
	int timeout = 900000;

	while (timeout > 0 && inb(devc->base) == 0x80)	/* Are we initializing */
		timeout--;

	if(reg < 32)
	{
		outb(((unsigned char) (reg & 0xff) | devc->MCE_bit), io_Index_Addr(devc));
		outb(((unsigned char) (data & 0xff)), io_Indexed_Data(devc));
	}
	else
	{
		int xreg, xra;
		
		xreg = (reg & 0xff) - 32;
		xra = (((xreg & 0x0f) << 4) & 0xf0) | 0x08 | ((xreg & 0x10) >> 2);
		outb(((unsigned char) (23 & 0xff) | devc->MCE_bit), io_Index_Addr(devc));
		outb(((unsigned char) (xra & 0xff)), io_Indexed_Data(devc));
		outb((unsigned char) (data & 0xff), io_Indexed_Data(devc));
	}
}