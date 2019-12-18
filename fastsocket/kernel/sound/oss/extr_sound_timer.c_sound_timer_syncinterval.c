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
 int /*<<< orphan*/  ticks_offs ; 
 scalar_t__ tmr2ticks (scalar_t__) ; 
 scalar_t__ tmr_ctr ; 
 scalar_t__ tmr_offs ; 
 unsigned int usecs_per_tmr ; 

void sound_timer_syncinterval(unsigned int new_usecs)
{
	/*
	 *    This routine is called by the hardware level if
	 *      the clock frequency has changed for some reason.
	 */
	tmr_offs = tmr_ctr;
	ticks_offs += tmr2ticks(tmr_ctr);
	tmr_ctr = 0;
	usecs_per_tmr = new_usecs;
}