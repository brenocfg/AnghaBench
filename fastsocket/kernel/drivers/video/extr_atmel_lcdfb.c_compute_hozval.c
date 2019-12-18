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
 unsigned long ATMEL_LCDC_DISTYPE ; 
 unsigned long ATMEL_LCDC_DISTYPE_STNCOLOR ; 
 unsigned long ATMEL_LCDC_DISTYPE_TFT ; 
 unsigned long ATMEL_LCDC_IFWIDTH ; 
 unsigned long ATMEL_LCDC_IFWIDTH_4 ; 
 unsigned long ATMEL_LCDC_IFWIDTH_8 ; 
 unsigned long ATMEL_LCDC_SCANMOD ; 
 unsigned long ATMEL_LCDC_SCANMOD_DUAL ; 
 unsigned long DIV_ROUND_UP (unsigned long,int) ; 
 scalar_t__ cpu_is_at32ap7000 () ; 
 scalar_t__ cpu_is_at91sam9261 () ; 
 scalar_t__ cpu_is_at91sam9g10 () ; 

__attribute__((used)) static unsigned long compute_hozval(unsigned long xres, unsigned long lcdcon2)
{
	unsigned long value;

	if (!(cpu_is_at91sam9261() || cpu_is_at91sam9g10()
		|| cpu_is_at32ap7000()))
		return xres;

	value = xres;
	if ((lcdcon2 & ATMEL_LCDC_DISTYPE) != ATMEL_LCDC_DISTYPE_TFT) {
		/* STN display */
		if ((lcdcon2 & ATMEL_LCDC_DISTYPE) == ATMEL_LCDC_DISTYPE_STNCOLOR) {
			value *= 3;
		}
		if ( (lcdcon2 & ATMEL_LCDC_IFWIDTH) == ATMEL_LCDC_IFWIDTH_4
		   || ( (lcdcon2 & ATMEL_LCDC_IFWIDTH) == ATMEL_LCDC_IFWIDTH_8
		      && (lcdcon2 & ATMEL_LCDC_SCANMOD) == ATMEL_LCDC_SCANMOD_DUAL ))
			value = DIV_ROUND_UP(value, 4);
		else
			value = DIV_ROUND_UP(value, 8);
	}

	return value;
}