#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct TYPE_3__ {int bits_per_pixel; } ;
struct TYPE_4__ {TYPE_1__ var; } ;
struct sa1100fb_info {int reg_lccr0; TYPE_2__ fb; } ;

/* Variables and functions */
 int GAFR ; 
 int GPDR ; 
 int GPIO_LDD10 ; 
 int GPIO_LDD11 ; 
 int GPIO_LDD12 ; 
 int GPIO_LDD13 ; 
 int GPIO_LDD14 ; 
 int GPIO_LDD15 ; 
 int GPIO_LDD8 ; 
 int GPIO_LDD9 ; 
 int LCCR0_Act ; 
 int LCCR0_CMS ; 
 int LCCR0_Color ; 
 int LCCR0_Dual ; 

__attribute__((used)) static void sa1100fb_setup_gpio(struct sa1100fb_info *fbi)
{
	u_int mask = 0;

	/*
	 * Enable GPIO<9:2> for LCD use if:
	 *  1. Active display, or
	 *  2. Color Dual Passive display
	 *
	 * see table 11.8 on page 11-27 in the SA1100 manual
	 *   -- Erik.
	 *
	 * SA1110 spec update nr. 25 says we can and should
	 * clear LDD15 to 12 for 4 or 8bpp modes with active
	 * panels.  
	 */
	if ((fbi->reg_lccr0 & LCCR0_CMS) == LCCR0_Color &&
	    (fbi->reg_lccr0 & (LCCR0_Dual|LCCR0_Act)) != 0) {
		mask = GPIO_LDD11 | GPIO_LDD10 | GPIO_LDD9  | GPIO_LDD8;

		if (fbi->fb.var.bits_per_pixel > 8 ||
		    (fbi->reg_lccr0 & (LCCR0_Dual|LCCR0_Act)) == LCCR0_Dual)
			mask |= GPIO_LDD15 | GPIO_LDD14 | GPIO_LDD13 | GPIO_LDD12;

	}

	if (mask) {
		GPDR |= mask;
		GAFR |= mask;
	}
}