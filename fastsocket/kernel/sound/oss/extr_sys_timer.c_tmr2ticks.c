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
 int HZ ; 
 int curr_tempo ; 
 int curr_timebase ; 

__attribute__((used)) static unsigned long
tmr2ticks(int tmr_value)
{
	/*
	 *    Convert timer ticks to MIDI ticks
	 */

	unsigned long tmp;
	unsigned long scale;

	/* tmr_value (ticks per sec) *
	   1000000 (usecs per sec) / HZ (ticks per sec) -=> usecs */
	tmp = tmr_value * (1000000 / HZ);
	scale = (60 * 1000000) / (curr_tempo * curr_timebase);	/* usecs per MIDI tick */
	return (tmp + scale / 2) / scale;
}