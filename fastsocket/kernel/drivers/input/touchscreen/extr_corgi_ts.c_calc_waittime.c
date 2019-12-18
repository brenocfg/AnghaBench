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
struct corgi_ts {TYPE_1__* machinfo; } ;
struct TYPE_2__ {unsigned long (* get_hsync_invperiod ) () ;} ;

/* Variables and functions */
 int get_clk_frequency_khz (int /*<<< orphan*/ ) ; 
 unsigned long stub1 () ; 

__attribute__((used)) static unsigned long calc_waittime(struct corgi_ts *corgi_ts)
{
	unsigned long hsync_invperiod = corgi_ts->machinfo->get_hsync_invperiod();

	if (hsync_invperiod)
		return get_clk_frequency_khz(0)*1000/hsync_invperiod;
	else
		return 0;
}