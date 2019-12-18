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
 int /*<<< orphan*/  ad1848_tmr_start (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_interval ; 
 int /*<<< orphan*/  sound_timer_syncinterval (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad1848_tmr_reprogram(int dev)
{
	/*
	 *    Audio driver has changed sampling rate so that a different xtal
	 *      oscillator was selected. We have to reprogram the timer rate.
	 */

	ad1848_tmr_start(dev, current_interval);
	sound_timer_syncinterval(current_interval);
}