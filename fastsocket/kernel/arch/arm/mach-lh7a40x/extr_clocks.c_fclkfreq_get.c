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
 unsigned int CSC_CLKSET ; 
 int MAINDIV1 (unsigned int) ; 
 int MAINDIV2 (unsigned int) ; 
 int PREDIV (unsigned int) ; 
 int PS (unsigned int) ; 
 int XTAL_IN ; 

unsigned int fclkfreq_get (void)
{
	unsigned int clkset = CSC_CLKSET;
	unsigned int gclk
		= XTAL_IN
		/ (1 << PS(clkset))
		* (MAINDIV1(clkset) + 2)
		/ (PREDIV(clkset)   + 2)
		* (MAINDIV2(clkset) + 2)
		;
	return gclk;
}