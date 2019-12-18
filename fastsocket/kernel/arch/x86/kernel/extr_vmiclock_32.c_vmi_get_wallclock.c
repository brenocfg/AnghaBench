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
struct TYPE_2__ {unsigned long long (* get_wallclock ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 
 unsigned long long stub1 () ; 
 TYPE_1__ vmi_timer_ops ; 

unsigned long vmi_get_wallclock(void)
{
	unsigned long long wallclock;
	wallclock = vmi_timer_ops.get_wallclock(); // nsec
	(void)do_div(wallclock, 1000000000);       // sec

	return wallclock;
}