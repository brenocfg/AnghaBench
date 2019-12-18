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

__attribute__((used)) static inline bool
ath5k_check_timer_win(int a, int b, int window, int intval)
{
	/*
	 * 1.) usually B should be A + window
	 * 2.) A already updated, B not updated yet
	 * 3.) A already updated and has wrapped around
	 * 4.) B has wrapped around
	 */
	if ((b - a == window) ||				/* 1.) */
	    (a - b == intval - window) ||			/* 2.) */
	    ((a | 0x10000) - b == intval - window) ||		/* 3.) */
	    ((b | 0x10000) - a == window))			/* 4.) */
		return true; /* O.K. */
	return false;
}