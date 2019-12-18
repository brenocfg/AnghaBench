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
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  _net_uptime ; 

void
net_update_uptime_with_time(const struct timeval *tvp)
{
	_net_uptime = tvp->tv_sec;
	/*
	 * Round up the timer to the nearest integer value because otherwise
	 * we might setup networking timers that are off by almost 1 second.
	 */
	if (tvp->tv_usec > 500000)
		_net_uptime++;
}