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
 unsigned long* CSR_TIMER1_VALUE ; 
 int tick_nsec ; 
 int timer1_latch ; 

__attribute__((used)) static unsigned long timer1_gettimeoffset (void)
{
	unsigned long value = timer1_latch - *CSR_TIMER1_VALUE;

	return ((tick_nsec / 1000) * value) / timer1_latch;
}