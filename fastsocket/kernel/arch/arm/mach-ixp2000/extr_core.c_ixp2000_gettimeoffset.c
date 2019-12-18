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
 unsigned long* missing_jiffy_timer_csr ; 
 unsigned long next_jiffy_time ; 
 unsigned long ticks_per_usec ; 

unsigned long ixp2000_gettimeoffset (void)
{
 	unsigned long offset;

	offset = next_jiffy_time - *missing_jiffy_timer_csr;

	return offset / ticks_per_usec;
}