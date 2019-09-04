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
struct TYPE_4__ {unsigned int tv_usec; int tv_sec; } ;
struct TYPE_3__ {unsigned int tv_usec; } ;
struct itimerval {TYPE_2__ it_value; TYPE_1__ it_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,struct itimerval*,struct itimerval*) ; 

unsigned ualarm(unsigned value, unsigned interval)
{
	struct itimerval it = {
		.it_interval.tv_usec = interval,
		.it_value.tv_usec = value
	};
	setitimer(ITIMER_REAL, &it, &it);
	return it.it_value.tv_sec*1000000 + it.it_value.tv_usec;
}