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
struct lcd_device {int dummy; } ;

/* Variables and functions */
 int FB_BLANK_POWERDOWN ; 
 int FB_BLANK_UNBLANK ; 
 int PPC_LDD2 ; 
 int PPSR ; 

__attribute__((used)) static int jornada_lcd_get_power(struct lcd_device *dev)
{
	/* LDD2 in PPC = LCD POWER */
	if (PPSR & PPC_LDD2)
		return FB_BLANK_UNBLANK;	/* PW ON */
	else
		return FB_BLANK_POWERDOWN;	/* PW OFF */
}