#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ (* rtc_set ) (scalar_t__,scalar_t__) ;} ;
struct TYPE_3__ {scalar_t__ rtcPop; scalar_t__ rtcDeadline; } ;

/* Variables and functions */
 scalar_t__ EndOfAllTime ; 
 scalar_t__ rtc_nanotime_read () ; 
 TYPE_2__* rtc_timer ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__) ; 
 TYPE_1__* x86_lcpu () ; 

uint64_t
setPop(uint64_t time)
{
	uint64_t	now;
	uint64_t	pop;

	/* 0 and EndOfAllTime are special-cases for "clear the timer" */
	if (time == 0 || time == EndOfAllTime ) {
		time = EndOfAllTime;
		now = 0;
		pop = rtc_timer->rtc_set(0, 0);
	} else {
		now = rtc_nanotime_read();	/* The time in nanoseconds */
		pop = rtc_timer->rtc_set(time, now);
	}

	/* Record requested and actual deadlines set */
	x86_lcpu()->rtcDeadline = time;
	x86_lcpu()->rtcPop	= pop;

	return pop - now;
}