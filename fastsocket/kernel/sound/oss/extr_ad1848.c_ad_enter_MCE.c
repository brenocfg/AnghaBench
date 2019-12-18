#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int MCE_bit; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ad1848_info ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_Index_Addr (TYPE_1__*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_enter_MCE(ad1848_info * devc)
{
	int timeout = 1000;
	unsigned short prev;

	while (timeout > 0 && inb(devc->base) == 0x80)	/*Are we initializing */
		timeout--;

	devc->MCE_bit = 0x40;
	prev = inb(io_Index_Addr(devc));
	if (prev & 0x40)
	{
		return;
	}
	outb((devc->MCE_bit), io_Index_Addr(devc));
}