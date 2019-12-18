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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  dccp_timestamp_seed ; 
 int /*<<< orphan*/  do_div (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 int /*<<< orphan*/  ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 dccp_timestamp(void)
{
	s64 delta = ktime_us_delta(ktime_get_real(), dccp_timestamp_seed);

	do_div(delta, 10);
	return delta;
}