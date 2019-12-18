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
typedef  int u64 ;
struct clock_event_device {int shift; int mult; } ;

/* Variables and functions */
 int LONG_MAX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 scalar_t__ unlikely (int) ; 

unsigned long clockevent_delta2ns(unsigned long latch,
				  struct clock_event_device *evt)
{
	u64 clc = ((u64) latch << evt->shift);

	if (unlikely(!evt->mult)) {
		evt->mult = 1;
		WARN_ON(1);
	}

	do_div(clc, evt->mult);
	if (clc < 1000)
		clc = 1000;
	if (clc > LONG_MAX)
		clc = LONG_MAX;

	return (unsigned long) clc;
}