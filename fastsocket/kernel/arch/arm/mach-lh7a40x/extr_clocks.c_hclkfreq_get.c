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
 int HCLKDIV (unsigned int) ; 
 int fclkfreq_get () ; 

unsigned int hclkfreq_get (void)
{
	unsigned int clkset = CSC_CLKSET;
	unsigned int hclk = fclkfreq_get () / (HCLKDIV(clkset) + 1);

	return hclk;
}