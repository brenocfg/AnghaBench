#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* tmr_start ) (int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int curr_tempo ; 
 int curr_timebase ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long) ; 
 TYPE_1__* tmr ; 
 int /*<<< orphan*/  usecs_per_tmr ; 

void reprogram_timer(void)
{
	unsigned long   usecs_per_tick;

	/*
	 *	The user is changing the timer rate before setting a timer
	 *	slap, bad bad not allowed.
	 */
	 
	if(!tmr)
		return;
		
	usecs_per_tick = (60 * 1000000) / (curr_tempo * curr_timebase);

	/*
	 * Don't kill the system by setting too high timer rate
	 */
	if (usecs_per_tick < 2000)
		usecs_per_tick = 2000;

	usecs_per_tmr = tmr->tmr_start(tmr->dev, usecs_per_tick);
}