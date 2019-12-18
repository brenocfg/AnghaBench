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
 int PPCR ; 
 int* cclk_frequency_100khz ; 

unsigned int cpufreq_get(unsigned int cpu)
{
	return cclk_frequency_100khz[PPCR & 0xf] * 100;
}