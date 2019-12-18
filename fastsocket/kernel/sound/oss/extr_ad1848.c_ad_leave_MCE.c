#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int MCE_bit; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ ad1848_info ;

/* Variables and functions */
 unsigned char ad_read (TYPE_1__*,int) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_Index_Addr (TYPE_1__*) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_calibration (TYPE_1__*) ; 

__attribute__((used)) static void ad_leave_MCE(ad1848_info * devc)
{
	unsigned char prev, acal;
	int timeout = 1000;

	while (timeout > 0 && inb(devc->base) == 0x80)	/*Are we initializing */
		timeout--;

	acal = ad_read(devc, 9);

	devc->MCE_bit = 0x00;
	prev = inb(io_Index_Addr(devc));
	outb((0x00), io_Index_Addr(devc));	/* Clear the MCE bit */

	if ((prev & 0x40) == 0)	/* Not in MCE mode */
	{
		return;
	}
	outb((0x00), io_Index_Addr(devc));	/* Clear the MCE bit */
	if (acal & 0x08)	/* Auto calibration is enabled */
		wait_for_calibration(devc);
}